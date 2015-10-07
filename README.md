# Smosh Video

**Q:** _What is smosh video?_

**A:** A (s)imple data(mosh) effect that operates on the three color channels in an image to give a 3D effect.

**Q:** _How do I use this?_

**A:** I am assuming basic knowledge of how to compile C++ programs. Compile with:

```sh
$ g++ $(pkg-config --cflags --libs opencv) smoshvid.cpp  -o smosh
```

Make sure you have the FFMPEG and OpenCv libraries installed in `/usr/lib/local `
This can be achieved with the following command for users with this handy guide: [Install OpenCV](https://www.youtube.com/watch?v=mJWVz3ncRoo) 

_Full disclosure: That is how I did it._

**Q:** _Now what?_

**A:** Find your favorite video and run the following:
        
```sh
$ ./smosh path/to/video/file
```

**Q:** _AWESOME! But is there a GUI/Non command line version of this available?_

**A:** Unfortunately, No (for the time being). Writing a UI in C++ is non-trivial however the plan is to take this and other effects to [insert app store here] as soon as I can, so consider this an early-stage alpha.

**Q:** _Can this do my laundry for me?_

**A:** No. Go [here](http://plcs.net/) to learn that.
