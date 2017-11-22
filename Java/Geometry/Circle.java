package Geom;

import java.util.ArrayList;

public  class Circle extends Util{
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
