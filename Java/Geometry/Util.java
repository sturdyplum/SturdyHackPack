package Geom;
import java.util.Arrays;

public class Util{

	// returns dot product of |a-b|*|b-c|
	public static double dot(Point a, Point b, Point c) {
		Point ab = new Point(b.x - a.x, b.y - a.y);
		Point bc = new Point(c.x - b.x, c.y - b.y);
		return ab.x * bc.x + ab.y * bc.y;
	}

	// return cross product of |b-a|x|c-a|
	public static double cross(Point a, Point b, Point c) {
		Point ab = new Point(b.x - a.x, b.y - a.y);
		Point ac = new Point(c.x - a.x, c.y - a.y);
		return ab.x * ac.y - ab.y * ac.x;
	}

	// returns if a,b,c are colinear
	public static boolean colinear(Point a, Point b, Point c) {
		return (a.x - b.x) * (a.y - c.y) == (a.x - c.x) * (a.y - b.y);
	}

	public static double hypot(double a, double b) {
		return Math.sqrt(a * a + b * b);
	}

	// returns distance between points a, and b
	public static double distance(Point a, Point b) {
		return hypot(a.x - b.x, a.y - b.y);
	}

	// returns true iff p lies in box with opposite corners b1, b2
	public static boolean point_in_box(Point p, Point b1, Point b2) {
		return ((p.x >= Math.min(b1.x, b2.x)) && (p.x <= Math.max(b1.x, b2.x)) && (p.y >= Math.min(b1.y, b2.y))
				&& (p.y <= Math.max(b1.y, b2.y)));
	}

	public static int testTriangle(double a, double b, double c) {
		double[] tri = new double[] { a, b, c };
		Arrays.sort(tri);
		double smallSides = tri[0] + tri[1];

		// Check degenerate case.
		if (eq(smallSides, tri[2]))
			return 1;
		if (smallSides > tri[2])
			return 2;
		return 0;
	}

	public static boolean eq(double a, double b) {
		return Math.abs(a - b) < EPS;
}
}
