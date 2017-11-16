import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Geometry {

	static double EPS = 1e-9;
	public static final int INF = Integer.MAX_VALUE >> 2;

	public static class Point implements Comparable<Point> {
		public double x;
		public double y;
		public double angle;
		public int idx;

		public Point(double x, double y) {
			this.x = x;
			this.y = y;
			angle = 0;
		}

		public Point(double x, double y, int idx) {
			this.x = x;
			this.y = y;
			this.idx = idx;
		}

		boolean equalTo(Point other) {
			return eq(other.x , x) && eq(other.y , y);
		}

		public int compareTo(Point other) {
			return x == other.x ? (int) Math.signum(y - other.y) : (int) Math.signum(x - other.x);
		}

		public Point sub(Point other) {
			return new Point(x - other.x, y - other.y);
		}

		public Point add(Point other) {
			return new Point(x + other.x, y + other.y);
		}

		Point scale(double s) {
			return new Point(x * s, y * s);
		}

		double mag2() {
			return x * x + y * y;
		}

		double mag() {
			return Math.sqrt(mag2());
		}

		public Point normalize() {
			return scale(1. / mag());
		}
		
		public String toString() {
			return "("+x+","+y+")";
		}
	}

	public static class Line {
		public double a, b, c;

		// ax + by = c

		/**
		 * Standard representation
		 */
		public Line(double a, double b, double c) {
			this.a = a;
			this.b = b;
			this.c = c;
		}

		/**
		 * Unique line between two points
		 */
		public Line(Point p1, Point p2) { // two points
			if (p1.x == p2.x) {
				a = 1;
				b = 0;
				c = -p1.x;
			} else {
				b = 1;
				a = -(p1.y - p2.y) / (p1.x - p2.x);
				c = -(a * p1.x) - (b * p1.y);
			}
		}

		double evaluate_x(double x) {
			return (c - a * x) / b;
		}

		/**
		 * Point-slope formula
		 */
		public Line(Point p, double m) {
			a = -m;
			b = 1;
			c = -((a * p.x) + (b * p.y));
		}

		// returns true if line l is parallel to this
		public boolean parallel(Line l) {
			return eq(a , l.a) && eq(b, l.b);
		}

		// tests if two lines describe the same object
		public boolean same_line(Line l) {
			return (parallel(l) && eq(c, l.c));
		}

		// finds intersection point between lines
		// if no intersection found, returns null;
		// if same line, returns INF, INF point
		public Point intersection_point(Line l) {
			Point p = new Point(INF, INF);
			if (same_line(l))
				return p;
			if (parallel(l))
				return null;

			p.x = (l.b * c - b * l.c) / (l.a * b - a * l.b);
			if (Math.abs(b) > EPS)
				p.y = -(a * p.x + c) / b;
			else
				p.y = -(l.a * p.x + l.c) / l.b;
			return p;
		}

		// Finds the point closest to p lying on this line
		public Point closest_Point(Point p) {
			Point p_c = new Point(INF, INF);
			if (Math.abs(b) <= EPS) {
				p_c.x = -c;
				p_c.y = p.y;
				return p_c;
			}
			if (Math.abs(a) <= EPS) {
				p_c.x = p.x;
				p_c.y = -c;
				return p_c;
			}
			Line perp = new Line(p, 1 / a);
			return intersection_point(perp);
		}

		boolean intersects_point(Point p) {
			return eq(p.y, evaluate_x(p.x));
		}

		/**
		 * RETURN VALUES: -1 = segment is part of line 0 = segment is parallel 1
		 * = intersection is beyond segment 2 = good intersection
		 */
		int Do_LS_intersect(Segment s) {
			Line temp = new Line(s.a, s.b);
			if (temp.same_line(this))
				return -1;
			if (temp.parallel(this))
				return 0;
			Point intersection = temp.intersection_point(this);
			if (s.ptDist(intersection) < EPS)
				return 2;
			else
				return 1;
		}

		/**
		 * Make sure that you check that there is an intersection first Using
		 * the code above.
		 */
		Point LS_intersect(Segment s) {
			Line temp = new Line(s.a, s.b);
			return temp.intersection_point(this);
		}

		double get_slope() {
			return -a / b;
		}

	}

	public static class Segment {
		public Point a, b;
		public double length;

		public Segment(Point a, Point b) {
			this.a = a;
			this.b = b;
			length = distance(a, b);
		}

		/**
		 * Returns shortest point distance
		 * 
		 * @param c
		 *            point we are considering
		 * @return shortest length from c to this segment
		 */
		public double ptDist(Point c) {
			if (dot(a, b, c) > 0)
				return distance(b, c);
			if (dot(b, a, c) > 0)
				return distance(a, c);
			if (length == 0)
				return distance(a, c);
			return Math.abs(cross(a, b, c) / length);
		}

		/**
		 * Returns a point that segment intersects with s
		 * 
		 * @param s
		 *            the segment that we are testing for intersection
		 * @return A wrapper containting a boolean and a point if boolean is
		 *         true and point is null this and s have infinitely many
		 *         intersections if boolean is true and point is not null this
		 *         and s intersect exactly once at point if boolean is false
		 *         (implies point is null) this and s do not intersect
		 */
		public Wrapper segments_intersect(Segment s) {
			Line l1 = new Line(a, b), l2 = new Line(s.a, s.b);
			Point p = new Point(0, 0);

			if (l1.same_line(l2))
				return new Wrapper((point_in_box(a, s.a, s.b) || point_in_box(b, s.a, s.b) || point_in_box(s.a, a, b)
						|| point_in_box(s.b, a, b)), null);

			if (l1.parallel(l2))
				return new Wrapper(false, null);

			p = l1.intersection_point(l2);

			return new Wrapper((point_in_box(p, a, b) && point_in_box(p, s.a, s.b)), p);
		}

		static class Wrapper {
			public boolean state;
			public Point p;

			public Wrapper(boolean _state, Point _p) {
				state = _state;
				p = _p;
			}
		}

		boolean intersects_point(Point p) {
			return ptDist(p) < EPS;
		}
	}

	public static class Circle {
		// circle centered at p with radius r
		public Point p;
		public double r;

		public Circle(double x, double y, double r) {
			p = new Point(x, y);
			this.r = r;
		}

		public boolean equalTo(Circle other) {
			return p.equalTo(other.p) && eq(other.r, r);
		}

		// finds unique circle from 3 points
		public Circle(Point a, Point b, Point c) {
			double da1 = 2 * (c.x - a.x);
			double da2 = 2 * (c.x - b.x);
			double db1 = 2 * (c.y - a.y);
			double db2 = 2 * (c.y - b.y);
			double dc1 = c.x * c.x - a.x * a.x + c.y * c.y - a.y * a.y;
			double dc2 = c.x * c.x - b.x * b.x + c.y * c.y - b.y * b.y;

			double x = 0, y = 0;
			if (Math.abs(da1) <= EPS) {
				y = dc1 / db1;
				x = (dc2 - db2 * y) / da2;
			} else {
				db2 -= db1 * da2 / da1;
				dc2 -= dc1 * da2 / da1;
				y = dc2 / db2;
				x = (dc1 - db1 * y) / da1;
			}
			p = new Point(x, y);
			r = distance(p, a);
		}

		public boolean contains(Point other) {
			return distance(other, p) < r;
		}

		public boolean is_on_or_in_circle(Point other) {
			double d = distance(other, p);
			return d < r || eq(d, r);
		}

		public boolean do_CL_intersect(Line l) {
			Point cp = l.closest_Point(p);
			return is_on_or_in_circle(cp);
		}

		/*
		 * Will return a segment with the intersection points if there is only
		 * one point (line is tangent) the segment will have the point and then
		 * null.
		 */
		public ArrayList<Point> CL_intersect(Line l) {
			Point cp = l.closest_Point(p);
			double dist = distance(cp, p);
			ArrayList<Point> ans = new ArrayList<>();
			if (eq(dist, r)) {
				ans.add(cp);
				return ans;
			}
			double theta = Math.acos(dist / r);
			double move = Math.sin(theta) * r;
 			double theta2 = Math.atan2(l.get_slope(), 1.0);
			double dx = move * Math.cos(theta2);
			double dy = move * Math.sin(theta2);
			ans.add(new Point(p.x + dx, p.y + dy));
			ans.add(new Point(p.x - dx, p.y - dy));
			return ans;
		}

		/*
		 * Finds the intersection of two circles. If the two circles are the
		 * same or if there is no intersection then it will return null twice.
		 */
		public ArrayList<Point> CC_intersection(Circle other) {
			ArrayList<Point> ans = new ArrayList<>();
			if (equalTo(other))
				return ans;

			double L = r;
			double R = other.r;
			double B = distance(p, other.p);

			int nSols = testTriangle(L, R, B);
			if (nSols == 0)
				return ans;
			double c = (B * B + L * L - R * R) / (2 * B);
			double b = Math.sqrt(Math.abs(L * L - c * c));
			Point u = other.p.sub(p).normalize();
			Point v = new Point(-u.y, u.x);
			Point vc = u.scale(c);
			Point vb = v.scale(b);

			if (nSols == 2) {
				ans.add(p.add(vc).add(vb));
			}
			ans.add(p.add(vc).sub(vb));
			return ans;
		}
	}

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
