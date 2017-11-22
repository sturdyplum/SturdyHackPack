package Geom;

public class Line extends Util{
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
