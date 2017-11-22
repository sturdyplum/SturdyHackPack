package Geom;
import java.util.ArrayList;


public class Polygon extends Util{

	ArrayList<Point> p = new ArrayList<>();
	int n;

	Polygon(ArrayList<Point> _p) {
		p = _p;
		n = p.size();
	}

	int prev(int i) {
		return i == 0 ? n - 1 : i - 1;
	}

	int next(int i) {
		return i == n - 1 ? 0 : i + 1;
	}

	/* Returns 2 * area of polygon to make this aaccurate make sure your points are integer based*/
	int area2() {
		int area = 0;
		for (int i = 0; i < n; i++) {
			area += p.get(i).x * (p.get(prev(i)).y - p.get(prev(i)).y);
		}
		return area;
	}

	/* Checks if a simple polygon is oriented in ccw */
	boolean orientation() {
		int minI = 0;
		for (int i = 0; i < n; i++) {
			if (p.get(i).compareTo(p.get(minI)) < 0) {
				minI = i;
			}
		}
		return cross(p.get(prev(minI)), p.get(minI), p.get(next(minI))) > 0;
	}
}
