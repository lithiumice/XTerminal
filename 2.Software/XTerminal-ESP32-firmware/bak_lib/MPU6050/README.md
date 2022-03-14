# I2CDEV_MPU6050
I2CDEV MPU-6050 6-axis accelerometer/gyroscope Arduino Library
adapted for Particle devices by Paul Kourany, April 2015

Updated to Particle Libraries v2.0, March 24, 2017

The MPU6050 combines a 3-axis gyroscope and a 3-axis accelerometer on the same silicon die together with
an onboard Digital Motion Processor(DMP) which processes complex 6-axis MotionFusion algorithms.

Original Library
----------------
https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050

I2CDevlib Website Link
----------------------
http://www.i2cdevlib.com/devices/mpu6050#source


Installing in the Spark.io Web IDE
----------------------------------

1. Open the Web based IDE on the Spark.io website.
2. Click on the Library button on the left hand side of the IDE. It looks like a little banner or flag...
3. Click "Contribute Library" button at the top of the panel that folded out.
4. Paste "JamesHagerman/MPU6050" into the text field (without quotes, of course).
5. Click "Add Repository".
6. Make sure the main window in the IDE says "Library is valid. Ready to import." at the top.
7. Click "Import".
8. Click "Got it, Proceed" if it asks you. This is basically because the True MPU6050 library is already there (but it's broken otherwise you wouldn't be reading this...)
9. You're done!

Look at the next section to actually use the library in a project. The "Use this example" button doesn't work with this library quite yet.

Using the library on the Spark.io Web IDE
-----------------------------------------

1. Create a new project in the Web based IDE on the Spark.io website. Remember the name for step 6.
2. Click the Library button the left hand side of the IDE. It still looks like a little banner or flag...
3. Select the MPU6050 Library from under the "My Libraries" section.
4. Make sure the version is at least "1.0.1"
5. Click "Include in App"
6. Select the app you just created (or whatever app you wanna use this library in)
7. Click "Add to this App"
8. You're done!

Now you just need some example code, right? You can find a (hopefully) working example at:
```
examples/spark_ide_example.c
```

You'll probably need to modify it pretty heavily to get it to do what you wanna do but at least it's spitting out data now!

Good luck!
