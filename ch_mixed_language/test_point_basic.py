#!/usr/bin/env python3
"""
Basic example of using the point_module Python extension.
This demonstrates simple pybind11 bindings for a C++ Point class.
"""

import sys
try:
    import point_module
except ImportError:
    print("Error: point_module not found.")
    print("Make sure the module is built and in the Python path.")
    print("You may need to add the build directory to PYTHONPATH.")
    sys.exit(1)

def main():
    print("=== Basic Point Module Example ===\n")
    
    # Create two points
    p1 = point_module.Point(0.0, 0.0)
    p2 = point_module.Point(3.0, 4.0)
    
    print(f"Created point p1 at origin")
    print(f"Created point p2 at (3.0, 4.0)")
    
    # Calculate distance
    dist = p1.distance_to(p2)
    print(f"\nDistance from p1 to p2: {dist:.2f}")
    print(f"Expected distance: 5.00 (3-4-5 triangle)")
    
    # More examples
    p3 = point_module.Point(1.0, 1.0)
    p4 = point_module.Point(4.0, 5.0)
    
    dist2 = p3.distance_to(p4)
    print(f"\nDistance from (1,1) to (4,5): {dist2:.2f}")
    
    print("\n? Basic pybind11 example completed successfully!")

if __name__ == "__main__":
    main()
