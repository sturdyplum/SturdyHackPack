package Geom;

public class Point extends Util implements Comparable<Point> {
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
