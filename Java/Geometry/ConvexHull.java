package Geom;

import java.util.ArrayList;
import java.util.Collections;

public class ConvexHull extends Util {
	static ArrayList<Point> hull;
	Point hullUp[], hullLow[];
	// Convex hull O(nlgn)
	// Returns the convex hull in COUNTER-CLOCKWISE order.
	// Assumes more than 1 point
	// Vector: Compare X then Y.
	ConvexHull(ArrayList<Point> ps) {
	    hull = (ArrayList<Point>) ps.clone();
	    Collections.sort(hull);
	    int n = hull.size();

	    Point[] lo = new Point[n];
	    lo[0] = hull.get(0);
	    lo[1] = hull.get(1);

	    int j = 2;
	                
	    for (int i = 2; i < n; i++) {
	    Point p = hull.get(i);
	        while (j > 1 && !rightTurn(lo[j - 2], lo[j - 1], p))
	            j--;
	        lo[j++] = p;
	    }
	                
	    Point[] up = new Point[n];
	                
	    up[0] = hull.get(n - 1); // note difference
	    up[1] = hull.get(n - 2);
	                
	    int k = 2;
	                
	    for (int i = n - 3; i >= 0; i--) { // note difference
	        Point p = hull.get(i);
	        while (k > 1 && !rightTurn(up[k - 2], up[k - 1], p))
	            k--;
	    up[k++] = p;
	    }
	                
	    ArrayList<Point> res = new ArrayList<Point>();
	    for (int i = 0; i < k; i++)
	        res.add(up[i]);
	    for (int i = 1; i < j - 1; i++) // note difference
	        res.add(lo[i]);

	    // Only needed if want the two halves of the polygon
	    Point[] upReal = new Point[k];
	    for(int i = 0; i < k; i++) upReal[i] = up[k - i - 1];
	    Point[] loReal = new Point[j];
	    for(int i = 0; i < j; i++) loReal[i] = lo[i];
	    hullUp = upReal; hullLow = loReal;

	    hull =  res;
	}

	public static boolean rightTurn(Point a, Point b, Point c) {
	    return cross(a,b,c)> 0;
	}
}
