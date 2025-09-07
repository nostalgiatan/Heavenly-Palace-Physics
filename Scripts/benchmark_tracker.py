#!/usr/bin/env python3
"""
Benchmark tracking and regression detection script for Jolt Physics
This script helps track performance over time and detect regressions.
"""

import json
import csv
import sys
import os
import argparse
import subprocess
import time
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional, Tuple


class BenchmarkTracker:
    """Tracks and analyzes benchmark results over time."""
    
    def __init__(self, results_dir: str = "benchmark-results"):
        self.results_dir = Path(results_dir)
        self.results_dir.mkdir(exist_ok=True)
        self.baseline_file = self.results_dir / "baseline.json"
        self.history_file = self.results_dir / "history.json"
        
    def load_baseline(self) -> Dict:
        """Load baseline performance metrics."""
        if self.baseline_file.exists():
            with open(self.baseline_file, 'r') as f:
                return json.load(f)
        return {}
    
    def save_baseline(self, baseline: Dict):
        """Save baseline performance metrics."""
        with open(self.baseline_file, 'w') as f:
            json.dump(baseline, f, indent=2)
    
    def load_history(self) -> List[Dict]:
        """Load performance history."""
        if self.history_file.exists():
            with open(self.history_file, 'r') as f:
                return json.load(f)
        return []
    
    def save_history(self, history: List[Dict]):
        """Save performance history."""
        with open(self.history_file, 'w') as f:
            json.dump(history, f, indent=2)
    
    def parse_performance_output(self, output: str) -> Dict:
        """Parse performance test CSV output into structured data."""
        lines = output.strip().split('\n')
        results = {}
        
        # Skip header and configuration lines
        data_lines = [line for line in lines if line and ',' in line and not line.startswith('Single precision')]
        
        for line in data_lines:
            parts = line.split(',')
            if len(parts) >= 4:
                motion_quality = parts[0].strip()
                thread_count = parts[1].strip()
                steps_per_second = parts[2].strip()
                hash_value = parts[3].strip()
                
                try:
                    steps_per_second = float(steps_per_second)
                    key = f"{motion_quality}_{thread_count}threads"
                    results[key] = {
                        'steps_per_second': steps_per_second,
                        'hash': hash_value,
                        'motion_quality': motion_quality,
                        'thread_count': thread_count
                    }
                except ValueError:
                    continue
                    
        return results
    
    def run_benchmark(self, scene: str, build_dir: str, iterations: int = 1000, 
                     repeats: int = 3) -> Optional[Dict]:
        """Run a specific benchmark and return results."""
        perf_test_path = Path(build_dir) / "PerformanceTest"
        if not perf_test_path.exists():
            print(f"Error: PerformanceTest not found at {perf_test_path}")
            return None
        
        cmd = [
            str(perf_test_path),
            f"-s={scene}",
            f"-i={iterations}",
            f"-repeat={repeats}",
            "-q=LinearCast",
            "-t=max"
        ]
        
        print(f"Running benchmark: {' '.join(cmd)}")
        
        try:
            result = subprocess.run(cmd, capture_output=True, text=True, timeout=300)
            if result.returncode == 0:
                return self.parse_performance_output(result.stdout)
            else:
                print(f"Benchmark failed: {result.stderr}")
                return None
        except subprocess.TimeoutExpired:
            print("Benchmark timed out")
            return None
        except Exception as e:
            print(f"Error running benchmark: {e}")
            return None
    
    def detect_regression(self, current_results: Dict, baseline: Dict, 
                         threshold: float = 0.1) -> List[Dict]:
        """Detect performance regressions compared to baseline."""
        regressions = []
        
        for key, current in current_results.items():
            if key in baseline:
                baseline_perf = baseline[key]['steps_per_second']
                current_perf = current['steps_per_second']
                change = (current_perf - baseline_perf) / baseline_perf
                
                if change < -threshold:  # Performance degraded by more than threshold
                    regressions.append({
                        'test': key,
                        'baseline_perf': baseline_perf,
                        'current_perf': current_perf,
                        'change_percent': change * 100,
                        'scene': current.get('scene', 'unknown')
                    })
        
        return regressions
    
    def generate_report(self, results: Dict, scene: str, build_type: str) -> str:
        """Generate a formatted report of benchmark results."""
        report = f"\n=== Benchmark Report: {scene} ({build_type}) ===\n"
        report += f"Timestamp: {datetime.now().isoformat()}\n\n"
        
        if not results:
            report += "No results available.\n"
            return report
        
        report += f"{'Test Configuration':<30} {'Steps/Second':<15} {'Hash':<20}\n"
        report += "-" * 70 + "\n"
        
        for key, data in results.items():
            report += f"{key:<30} {data['steps_per_second']:<15.2f} {data['hash'][:16]:<20}\n"
        
        return report
    
    def update_history(self, results: Dict, scene: str, build_type: str, 
                      commit_hash: str = None):
        """Add current results to history."""
        history = self.load_history()
        
        entry = {
            'timestamp': datetime.now().isoformat(),
            'scene': scene,
            'build_type': build_type,
            'commit_hash': commit_hash or self.get_git_commit(),
            'results': results
        }
        
        history.append(entry)
        self.save_history(history)
    
    def get_git_commit(self) -> str:
        """Get current git commit hash."""
        try:
            result = subprocess.run(['git', 'rev-parse', 'HEAD'], 
                                  capture_output=True, text=True)
            if result.returncode == 0:
                return result.stdout.strip()
        except:
            pass
        return "unknown"
    
    def set_baseline(self, scene: str, build_dir: str, build_type: str = "Release"):
        """Set new baseline for a scene."""
        print(f"Setting baseline for {scene}...")
        results = self.run_benchmark(scene, build_dir)
        
        if results:
            baseline = self.load_baseline()
            baseline[f"{scene}_{build_type}"] = {
                'timestamp': datetime.now().isoformat(),
                'commit_hash': self.get_git_commit(),
                'results': results
            }
            self.save_baseline(baseline)
            print(f"Baseline set for {scene} ({build_type})")
            print(self.generate_report(results, scene, build_type))
        else:
            print(f"Failed to set baseline for {scene}")
    
    def check_regression(self, scene: str, build_dir: str, build_type: str = "Release",
                        threshold: float = 0.1) -> bool:
        """Check for performance regression against baseline."""
        print(f"Checking regression for {scene}...")
        
        current_results = self.run_benchmark(scene, build_dir)
        if not current_results:
            print("Failed to run benchmark")
            return False
        
        # Update history
        self.update_history(current_results, scene, build_type)
        
        baseline = self.load_baseline()
        baseline_key = f"{scene}_{build_type}"
        
        if baseline_key not in baseline:
            print(f"No baseline found for {scene} ({build_type}). Setting current as baseline.")
            self.set_baseline(scene, build_dir, build_type)
            return False
        
        baseline_results = baseline[baseline_key]['results']
        regressions = self.detect_regression(current_results, baseline_results, threshold)
        
        print(self.generate_report(current_results, scene, build_type))
        
        if regressions:
            print("\n⚠️  PERFORMANCE REGRESSIONS DETECTED:")
            for reg in regressions:
                print(f"  - {reg['test']}: {reg['change_percent']:.2f}% slower "
                      f"({reg['current_perf']:.2f} vs {reg['baseline_perf']:.2f} steps/sec)")
            return True
        else:
            print("✅ No significant performance regressions detected.")
            return False


def main():
    parser = argparse.ArgumentParser(description="Benchmark tracker for Jolt Physics")
    parser.add_argument('command', choices=['baseline', 'check', 'report', 'history'],
                       help='Command to execute')
    parser.add_argument('--scene', default='ConvexVsMesh',
                       choices=['ConvexVsMesh', 'Ragdoll', 'Pyramid', 'LargeMesh'],
                       help='Scene to benchmark')
    parser.add_argument('--build-dir', required=True,
                       help='Path to build directory containing PerformanceTest')
    parser.add_argument('--build-type', default='Release',
                       help='Build type (Release, Distribution, etc.)')
    parser.add_argument('--threshold', type=float, default=0.1,
                       help='Regression threshold (default: 0.1 = 10%)')
    parser.add_argument('--results-dir', default='benchmark-results',
                       help='Directory to store results')
    
    args = parser.parse_args()
    
    tracker = BenchmarkTracker(args.results_dir)
    
    if args.command == 'baseline':
        tracker.set_baseline(args.scene, args.build_dir, args.build_type)
    elif args.command == 'check':
        has_regression = tracker.check_regression(args.scene, args.build_dir, 
                                                 args.build_type, args.threshold)
        sys.exit(1 if has_regression else 0)
    elif args.command == 'report':
        results = tracker.run_benchmark(args.scene, args.build_dir)
        if results:
            print(tracker.generate_report(results, args.scene, args.build_type))
    elif args.command == 'history':
        history = tracker.load_history()
        if history:
            print("Benchmark History:")
            for entry in history[-10:]:  # Show last 10 entries
                print(f"  {entry['timestamp']}: {entry['scene']} "
                      f"({entry['build_type']}) - {entry['commit_hash'][:8]}")
        else:
            print("No benchmark history found.")


if __name__ == '__main__':
    main()