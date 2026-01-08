#!/usr/bin/env python3
"""
Advanced example of using the point_advanced Python extension.
This demonstrates more sophisticated pybind11 bindings including:
- Properties
- Overloaded methods
- Container classes
- Special Python methods (__repr__, __str__, __len__, __getitem__)
"""

import sys
try:
    import point_advanced
except ImportError:
    print("Error: point_advanced module not found.")
    print("Make sure the module is built and in the Python path.")
    print("You may need to add the build directory to PYTHONPATH.")
    sys.exit(1)

def main():
    print("=== Advanced Point Module Example ===\n")
    
    # Test Point class with properties
    print("1. Testing Point class with properties:")
    p = point_advanced.Point(10.0, 20.0)
    print(f"   Created point: {p}")
    print(f"   X coordinate: {p.x}")
    print(f"   Y coordinate: {p.y}")
    
    # Modify using properties
    p.x = 15.0
    p.y = 25.0
    print(f"   Modified point: {p}")
    
    # Test PointCloud class
    print("\n2. Testing PointCloud class:")
    cloud = point_advanced.PointCloud()
    
    # Add points using different methods
    cloud.add_point(0.0, 0.0)
    cloud.add_point(1.0, 0.0)
    cloud.add_point(1.0, 1.0)
    cloud.add_point(0.0, 1.0)
    
    # Can also add Point objects
    cloud.add_point(point_advanced.Point(0.0, 0.0))
    
    print(f"   Number of points: {len(cloud)}")
    
    # Access points using indexing
    print("\n3. Accessing points by index:")
    for i in range(len(cloud)):
        print(f"   cloud[{i}] = {cloud[i]}")
    
    # Calculate total distance
    total_dist = cloud.total_distance()
    print(f"\n4. Total path distance: {total_dist:.2f}")
    
    # Calculate centroid
    center = cloud.centroid()
    print(f"   Centroid: {center}")
    
    # More complex example: create a circle of points
    print("\n5. Creating a circle of points:")
    import math
    circle = point_advanced.PointCloud()
    n_points = 8
    radius = 5.0
    
    for i in range(n_points):
        angle = 2 * math.pi * i / n_points
        x = radius * math.cos(angle)
        y = radius * math.sin(angle)
        circle.add_point(x, y)
    
    print(f"   Circle with {len(circle)} points, radius {radius}")
    print(f"   Centroid: {circle.centroid()}")
    print(f"   Expected centroid: Point(0, 0)")
    
    # Calculate approximate circumference
    approx_circumference = circle.total_distance()
    expected_circumference = 2 * math.pi * radius
    print(f"   Approximate circumference: {approx_circumference:.2f}")
    print(f"   Expected circumference: {expected_circumference:.2f}")
    print(f"   Error: {abs(approx_circumference - expected_circumference):.2f}")
    
    print("\n? Advanced pybind11 example completed successfully!")

if __name__ == "__main__":
    main()
