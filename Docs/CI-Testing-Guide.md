# Enhanced CI/CD System for Jolt Physics

This document describes the enhanced continuous integration and testing system for the Jolt Physics engine.

## Overview

The enhanced CI system provides:

1. **Comprehensive Testing Framework**
   - Unit tests with extended categories
   - Performance benchmarks with regression detection  
   - Integration tests with multiple scenarios
   - Memory leak detection
   - Stress testing capabilities

2. **Benchmark Tracking System**
   - Automated baseline establishment
   - Performance regression detection
   - Historical performance tracking
   - Cross-platform determinism validation

3. **Enhanced GitHub Actions Workflows**
   - Benchmark performance workflow
   - Integration testing workflow
   - Extended testing with memory analysis

## Test Categories

### 1. Unit Tests (`UnitTests`)
- **Location**: `UnitTests/` directory
- **Framework**: doctest
- **Coverage**: 556 test cases, 458,894 assertions
- **Labels**: `unit`, `core`
- **Execution**: `./UnitTests` or `ctest`

### 2. Performance Tests (`PerformanceTest`)
- **Location**: `PerformanceTest/` directory
- **Scenes**: ConvexVsMesh, Ragdoll, Pyramid, LargeMesh
- **Labels**: `performance`, `benchmark`
- **Execution**: Various configurations via command line

### 3. Memory Tests
- **Tool**: Valgrind (Linux only)
- **Type**: Memory leak detection, heap profiling
- **Labels**: `memory`, `valgrind`
- **Execution**: `ctest -L memory`

### 4. Stress Tests
- **Type**: Extended duration testing
- **Labels**: `stress`, `extended`
- **Execution**: `ctest -L stress`

## Benchmark System

### Setting Baselines

```bash
# Individual scene baselines
make benchmark-baseline-convex
make benchmark-baseline-ragdoll
make benchmark-baseline-pyramid

# All baselines at once
make benchmark-baseline-all
```

### Checking for Regressions

```bash
# Individual scene regression checks
make benchmark-check-convex
make benchmark-check-ragdoll
make benchmark-check-pyramid

# All regression checks
make benchmark-check-all
```

### Generating Reports

```bash
# Quick benchmark report
make benchmark-report

# View benchmark history
make benchmark-history
```

### Python Benchmark Tracker

The `Scripts/benchmark_tracker.py` script provides advanced benchmark management:

```bash
# Set baseline for a scene
python3 Scripts/benchmark_tracker.py baseline --scene ConvexVsMesh --build-dir Build/Linux_Release

# Check for regressions (returns exit code 1 if regressions detected)
python3 Scripts/benchmark_tracker.py check --scene ConvexVsMesh --build-dir Build/Linux_Release --threshold 0.1

# Generate detailed report
python3 Scripts/benchmark_tracker.py report --scene ConvexVsMesh --build-dir Build/Linux_Release

# View historical data
python3 Scripts/benchmark_tracker.py history --results-dir benchmark-results
```

## GitHub Actions Workflows

### 1. Benchmark Performance (`.github/workflows/benchmark.yml`)

**Triggers**: Push to master, PR, daily schedule, manual dispatch

**Jobs**:
- `benchmark-performance`: Runs performance tests across multiple build types and compilers
- `memory-benchmarks`: Memory usage analysis with Valgrind
- `determinism-benchmark`: Cross-platform determinism validation
- `compare-benchmarks`: Generates performance comparison reports

**Artifacts**:
- Benchmark results (30 days retention)
- Memory analysis reports (30 days retention)
- Determinism validation logs (30 days retention)
- Performance comparison summary (90 days retention)

### 2. Integration Tests (`.github/workflows/integration.yml`)

**Triggers**: Push to master, PR, manual dispatch

**Jobs**:
- `integration-tests`: Basic integration testing with multiple build types
- `extended-integration`: Advanced testing with memory leak detection and profiling
- `summary`: Generates comprehensive test result summary

**Features**:
- HelloWorld integration testing
- Performance integration validation
- CTest framework integration
- Determinism validation
- Multi-threaded stress testing

## CTest Integration

### Running All Tests
```bash
ctest --output-on-failure --verbose
```

### Running Specific Test Categories
```bash
# Unit tests only
ctest -L unit

# Performance tests only  
ctest -L performance

# Memory tests (if Valgrind available)
ctest -L memory

# Stress tests
ctest -L stress
```

### Parallel Test Execution
```bash
# Run tests in parallel
ctest -j $(nproc)
```

## Performance Regression Detection

The system automatically detects performance regressions by:

1. **Baseline Comparison**: Compares current results against established baselines
2. **Threshold Configuration**: Configurable regression thresholds (default: 10%)
3. **Historical Tracking**: Maintains performance history for trend analysis
4. **CI Integration**: Fails CI builds when significant regressions are detected

### Configuration Options

**Regression Threshold**: Adjust sensitivity in `benchmark_tracker.py`
```python
--threshold 0.1  # 10% regression threshold
--threshold 0.05 # 5% regression threshold (more sensitive)
```

**Test Duration**: Configure test iterations for accuracy vs. speed
```bash
# Quick tests (faster CI)
./PerformanceTest -s=ConvexVsMesh -i=100

# Thorough tests (more accurate)
./PerformanceTest -s=ConvexVsMesh -i=1000 -repeat=3
```

## Memory Analysis

### Valgrind Integration
- **Tool**: Memcheck for leak detection
- **Configuration**: Full leak checking with origin tracking
- **Output**: Detailed leak reports in CI artifacts
- **Platforms**: Linux only (Valgrind limitation)

### Memory Test Execution
```bash
# Manual memory testing
valgrind --tool=memcheck --leak-check=full ./UnitTests

# CTest memory testing
ctest -L memory --output-on-failure
```

## Build Targets

### Standard Targets
- `Jolt`: Core physics library
- `UnitTests`: Unit test executable
- `PerformanceTest`: Performance testing executable
- `HelloWorld`: Basic integration example

### Enhanced Benchmark Targets
- `benchmark-baseline-*`: Set performance baselines
- `benchmark-check-*`: Check for regressions
- `benchmark-report`: Generate performance reports
- `benchmark-history`: View performance history

## CI Artifact Management

### Artifact Types and Retention

1. **Benchmark Results** (30 days)
   - Performance test outputs
   - Regression analysis results
   - Cross-compiler comparisons

2. **Memory Analysis** (30 days)
   - Valgrind leak reports
   - Memory usage profiles
   - Heap analysis data

3. **Integration Results** (30 days)
   - Integration test logs
   - Stress test outputs
   - Determinism validation

4. **Test Summaries** (90 days)
   - Comprehensive result overviews
   - Performance trend analysis
   - Historical comparisons

## Usage Examples

### Daily Development Workflow

```bash
# 1. Build and test
cd Build
./cmake_linux_clang_gcc.sh Release clang++
make -j $(nproc)
make test

# 2. Run benchmarks
make benchmark-check-all

# 3. Check for memory issues (Linux)
ctest -L memory
```

### Performance Regression Investigation

```bash
# 1. Check current performance
python3 Scripts/benchmark_tracker.py check --scene ConvexVsMesh --build-dir Build/Linux_Release

# 2. Generate detailed report
python3 Scripts/benchmark_tracker.py report --scene ConvexVsMesh --build-dir Build/Linux_Release

# 3. View historical trends
python3 Scripts/benchmark_tracker.py history
```

### CI Configuration Validation

```bash
# Test GitHub Actions workflows locally (with act or similar)
act push

# Validate specific workflow
act -j benchmark-performance
```

## Troubleshooting

### Common Issues

1. **Benchmark Variance**: Performance tests may show variance due to system load
   - Solution: Use `--repeat` flag for multiple runs
   - Consider CI environment consistency

2. **Memory Test Failures**: Valgrind may report false positives
   - Solution: Review Valgrind output carefully
   - Consider suppression files for known issues

3. **Timeout Issues**: Some tests may timeout in CI
   - Solution: Adjust timeout values in workflow files
   - Optimize test parameters for CI environment

### Performance Debugging

```bash
# Enable profiling
./PerformanceTest -s=ConvexVsMesh -p

# Use frame timing analysis
./PerformanceTest -s=ConvexVsMesh -f

# Enable debug renderer output
./PerformanceTest -s=ConvexVsMesh -r
```

## Future Enhancements

Potential improvements to the CI system:

1. **Performance Visualization**: Graphical performance trend dashboards
2. **Cross-Platform Comparison**: Automated performance comparisons across platforms
3. **Load Testing**: Automated stress testing with varying workloads
4. **Security Testing**: Static analysis integration
5. **Code Coverage**: Enhanced coverage reporting and tracking

## Contributing

When contributing to the CI system:

1. **Test Locally**: Verify changes work in local environment
2. **Update Documentation**: Keep this guide current with changes
3. **Consider Performance**: Ensure CI changes don't significantly slow builds
4. **Validate Cross-Platform**: Test changes across supported platforms
5. **Monitor Resources**: Be mindful of CI resource usage and costs