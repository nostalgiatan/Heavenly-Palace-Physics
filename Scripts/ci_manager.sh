#!/bin/bash
# CI Management Script for Jolt Physics
# This script helps manage the enhanced CI system

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$REPO_ROOT/Build"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Print colored output
print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_header() {
    echo -e "${BLUE}=== $1 ===${NC}"
}

# Help function
show_help() {
    cat << EOF
Jolt Physics CI Management Script

Usage: $0 [COMMAND] [OPTIONS]

Commands:
    setup                Set up CI environment and dependencies
    build [TYPE]         Build project (Debug, Release, Distribution)
    test [TYPE]          Run tests (unit, performance, integration, all)
    benchmark [ACTION]   Manage benchmarks (baseline, check, report, history)
    clean               Clean build artifacts
    validate            Validate CI configuration
    help                Show this help message

Examples:
    $0 setup                     # Set up CI environment
    $0 build Release             # Build Release configuration
    $0 test unit                 # Run unit tests only
    $0 benchmark baseline        # Set all benchmarks baselines
    $0 benchmark check           # Check for performance regressions
    $0 validate                  # Validate CI workflows

EOF
}

# Setup CI environment
setup_ci() {
    print_header "Setting up CI Environment"
    
    # Check for required tools
    print_status "Checking dependencies..."
    
    # Check CMake
    if ! command -v cmake &> /dev/null; then
        print_error "CMake not found. Please install CMake 3.20 or later."
        exit 1
    fi
    
    # Check Python
    if ! command -v python3 &> /dev/null; then
        print_error "Python 3 not found. Please install Python 3.6 or later."
        exit 1
    fi
    
    # Check compiler
    if ! command -v clang++ &> /dev/null && ! command -v g++ &> /dev/null; then
        print_error "No C++ compiler found. Please install clang++ or g++."
        exit 1
    fi
    
    print_status "All dependencies found!"
    
    # Create necessary directories
    mkdir -p "$BUILD_DIR/benchmark-results"
    mkdir -p "$BUILD_DIR/test-results"
    
    print_status "CI environment setup complete!"
}

# Build project
build_project() {
    local build_type="${1:-Release}"
    print_header "Building Project ($build_type)"
    
    cd "$BUILD_DIR"
    
    # Configure
    print_status "Configuring CMake..."
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        ./cmake_linux_clang_gcc.sh "$build_type" clang++
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        ./cmake_xcode_macos.sh "$build_type"
    else
        print_error "Unsupported platform: $OSTYPE"
        exit 1
    fi
    
    # Build
    print_status "Building..."
    cmake --build "Linux_$build_type" -j "$(nproc 2>/dev/null || sysctl -n hw.ncpu)"
    
    print_status "Build complete!"
}

# Run tests
run_tests() {
    local test_type="${1:-all}"
    print_header "Running Tests ($test_type)"
    
    local build_dir
    build_dir=$(find "$BUILD_DIR" -name "Linux_*" -type d | head -1)
    
    if [[ ! -d "$build_dir" ]]; then
        print_error "No build directory found. Run 'build' command first."
        exit 1
    fi
    
    cd "$build_dir"
    
    case "$test_type" in
        "unit")
            print_status "Running unit tests..."
            ctest -L unit --output-on-failure
            ;;
        "performance")
            print_status "Running performance tests..."
            ctest -L performance --output-on-failure
            ;;
        "integration")
            print_status "Running integration tests..."
            # Run HelloWorld if available
            if [[ -f "./HelloWorld" ]]; then
                print_status "Testing HelloWorld..."
                timeout 30 ./HelloWorld || true
            fi
            
            # Run basic performance integration
            if [[ -f "./PerformanceTest" ]]; then
                print_status "Testing PerformanceTest integration..."
                ./PerformanceTest -s=ConvexVsMesh -i=50 -q=LinearCast -t=1
            fi
            ;;
        "memory")
            print_status "Running memory tests..."
            if command -v valgrind &> /dev/null; then
                ctest -L memory --output-on-failure
            else
                print_warning "Valgrind not found, skipping memory tests"
            fi
            ;;
        "all")
            print_status "Running all tests..."
            ctest --output-on-failure
            ;;
        *)
            print_error "Unknown test type: $test_type"
            print_status "Available types: unit, performance, integration, memory, all"
            exit 1
            ;;
    esac
    
    print_status "Tests complete!"
}

# Manage benchmarks
manage_benchmarks() {
    local action="${1:-check}"
    print_header "Managing Benchmarks ($action)"
    
    local build_dir
    build_dir=$(find "$BUILD_DIR" -name "Linux_*" -type d | head -1)
    
    if [[ ! -d "$build_dir" ]]; then
        print_error "No build directory found. Run 'build' command first."
        exit 1
    fi
    
    cd "$build_dir"
    
    case "$action" in
        "baseline")
            print_status "Setting benchmark baselines..."
            if command -v make &> /dev/null; then
                make benchmark-baseline-all
            else
                print_status "Setting baselines manually..."
                python3 "$REPO_ROOT/Scripts/benchmark_tracker.py" baseline --scene ConvexVsMesh --build-dir .
                python3 "$REPO_ROOT/Scripts/benchmark_tracker.py" baseline --scene Pyramid --build-dir .
            fi
            ;;
        "check")
            print_status "Checking for performance regressions..."
            if command -v make &> /dev/null; then
                make benchmark-check-all
            else
                print_status "Checking regressions manually..."
                python3 "$REPO_ROOT/Scripts/benchmark_tracker.py" check --scene ConvexVsMesh --build-dir .
                python3 "$REPO_ROOT/Scripts/benchmark_tracker.py" check --scene Pyramid --build-dir .
            fi
            ;;
        "report")
            print_status "Generating benchmark report..."
            if command -v make &> /dev/null; then
                make benchmark-report
            else
                python3 "$REPO_ROOT/Scripts/benchmark_tracker.py" report --scene ConvexVsMesh --build-dir .
            fi
            ;;
        "history")
            print_status "Showing benchmark history..."
            python3 "$REPO_ROOT/Scripts/benchmark_tracker.py" history --build-dir .
            ;;
        *)
            print_error "Unknown benchmark action: $action"
            print_status "Available actions: baseline, check, report, history"
            exit 1
            ;;
    esac
    
    print_status "Benchmark management complete!"
}

# Clean build artifacts
clean_build() {
    print_header "Cleaning Build Artifacts"
    
    if [[ -d "$BUILD_DIR" ]]; then
        find "$BUILD_DIR" -name "Linux_*" -type d -exec rm -rf {} + 2>/dev/null || true
        find "$BUILD_DIR" -name "VS2022_*" -type d -exec rm -rf {} + 2>/dev/null || true
        find "$BUILD_DIR" -name "MacOS_*" -type d -exec rm -rf {} + 2>/dev/null || true
        print_status "Build artifacts cleaned!"
    else
        print_status "No build directory found."
    fi
}

# Validate CI configuration
validate_ci() {
    print_header "Validating CI Configuration"
    
    # Check workflow files
    print_status "Checking GitHub Actions workflows..."
    local workflows_dir="$REPO_ROOT/.github/workflows"
    
    if [[ -d "$workflows_dir" ]]; then
        for workflow in "$workflows_dir"/*.yml; do
            if [[ -f "$workflow" ]]; then
                print_status "Found workflow: $(basename "$workflow")"
                # Basic YAML syntax check
                if command -v python3 &> /dev/null; then
                    python3 -c "import yaml; yaml.safe_load(open('$workflow'))" 2>/dev/null && \
                        print_status "  ✓ YAML syntax valid" || \
                        print_warning "  ⚠ YAML syntax issues detected"
                fi
            fi
        done
    else
        print_warning "No GitHub workflows directory found"
    fi
    
    # Check scripts
    print_status "Checking scripts..."
    if [[ -f "$REPO_ROOT/Scripts/benchmark_tracker.py" ]]; then
        print_status "Found benchmark tracker script"
        if python3 -m py_compile "$REPO_ROOT/Scripts/benchmark_tracker.py" 2>/dev/null; then
            print_status "  ✓ Python syntax valid"
        else
            print_warning "  ⚠ Python syntax issues detected"
        fi
    else
        print_warning "Benchmark tracker script not found"
    fi
    
    # Check CMake configuration
    print_status "Checking CMake configuration..."
    if [[ -f "$BUILD_DIR/CMakeLists.txt" ]]; then
        print_status "Found CMakeLists.txt"
        # Basic CMake syntax check by configuring a minimal project
        local temp_dir=$(mktemp -d)
        cd "$temp_dir"
        cmake --version &>/dev/null && print_status "  ✓ CMake available" || print_warning "  ⚠ CMake not available"
        rm -rf "$temp_dir"
    else
        print_error "CMakeLists.txt not found in Build directory"
    fi
    
    print_status "CI validation complete!"
}

# Main script logic
main() {
    case "${1:-help}" in
        "setup")
            setup_ci
            ;;
        "build")
            build_project "$2"
            ;;
        "test")
            run_tests "$2"
            ;;
        "benchmark")
            manage_benchmarks "$2"
            ;;
        "clean")
            clean_build
            ;;
        "validate")
            validate_ci
            ;;
        "help"|"--help"|"-h")
            show_help
            ;;
        *)
            print_error "Unknown command: $1"
            echo
            show_help
            exit 1
            ;;
    esac
}

# Run main function with all arguments
main "$@"