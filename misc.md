Genome is a concatenated vector of N poly-specs

Poly-spec is a color-spec concat with K vertex-specs

A color-spec is a 32-bit YUVA color, with each channel represented as a gray code

A vertex-spec is a pair of 16-bit scaled integers, represented as a gray code.

The integers are scaled so that:

float(x) = x * width / 65535.0f

And a value of 0xFFFF, 0xFFFF indicates "end of polygon."

All polygons will be made into convex polygons.

The cost function is applied as follows:

For each 8x8 window in the image, apply SSIM (in what space?)

The average SSIM is the quality measurement

The SSIM values can be cached for regions and only updated for dirty

Gaussian mutation converts a value to float, adds a Gaussian random value, clips, then converts back to internal representation

Bitwise mutation changes each bit with a probability p

Crossover can be polygon-aligned, with cuts to be selected with 50% probability

Rendering will be performed by SDL2_gfx, dumping the result to some image format I can manipulate

Loading and saving images will initially be prototyped with byteimage.