#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)

typedef long long ll;

struct point{
    int x,y
};

point p0;

point next_to_top(stack<point>& s){
    point temp = s.top();
    s.pop();
    point dist = s.top();
    s.push(temp);
    return dist;
}

void swappoints(point& p1 , point& p2){
    point temp = p1;
    p1 = p2;
    p2 = temp;
}

ll distsq(point p1 , point p2){
    return ((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   // Find orientation
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? false : true;

   return (o == 2)? false: true;
}

void convexhull(point points[],ll n){
    int ymin = points[0].y;
    int _min = 0;
    for(int i = 1 ; i < n ; i++){
        int y = points[i].y;
        if(y < ymin || y == ymin && points[i].x < points[_min].x){
            ymin = y;
            _min = i;
        }
    }
    swappoints(points[_min],points[0]);
    p0 = points[0];
    sort(points+1,points+n,compare);
    int m = 1;
    for(int i = 1 ; i < n ; i++){
        while(i < n-1 && orientation(p0,points[i],points[i+1])==0)
            i++;
        points[m] = points[i];
        m++;
    }
    if(m<3) return;
    stack<point> s;
    s.push(points[0]);
    s.push(points[1]);
    s.push(points[2]);

    for(int i = 3 ; i < m ; i++){
        while(orientation(next_to_top(s),s.top(),points[i])!=2)
            s.pop();
        s.push(points[i]);
    }

    while(!s.empty()){
        point t = s.top();
        s.pop();
        cout << t.x << " " << t.y << endl;
    }
    }

int main()
{
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(points)/sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
