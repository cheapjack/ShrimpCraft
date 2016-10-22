scalar = 1;

wingrotx=90;
wingroty=0;
wingrotz=0;

scale([scalar,scalar,scalar])rotate([wingrotx, wingroty, wingrotz])translate([1, 11.9, 3.2])import ("/Users/Power5/Downloads/petridishholderpt1.stl
", convexity = 3);

rotate([180, 180, 0])translate([-50, -52, 0])import("/Users/Power5/Downloads/RaspberryPi2_Tray_Basic_v1.0.stl", convexity = 3);