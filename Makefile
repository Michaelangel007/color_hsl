all: hue2rgb
clean:
	rm hue2rgb

hue2rgb: hsl_to_rgb.cpp
	g++ $< -o $@

