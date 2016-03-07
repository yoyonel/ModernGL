from PIL import Image, ImageDraw, ImageFont
import struct, textwrap, sys

size = 16

alphabet = ''.join(chr(i) if i in range(32, 127) else '•' for i in range(256))
font = ImageFont.truetype('Data\\DroidSansMono\\DroidSansMono.ttf', size)
width, height = (0, 0)
wpad, hpad = (2, 2)

for glyph in alphabet:
	w, h = font.getsize(glyph)

	if width < w:
		width = w

	if height < h:
		height = h

padded_width = width + wpad * 2
padded_height = height + hpad * 2

image = Image.new('RGBA', (padded_width * 16, padded_height * 16))
draw = ImageDraw.Draw(image)

for i, glyph in enumerate(alphabet):
	draw.text(((i % 16) * padded_width + wpad, (i // 16) * padded_height + hpad), glyph, font = font)

pixel = image.load()
w, h = image.size

pixels = bytearray()
for y in range(h):
	for x in range(w):
		pixels.append(pixel[x, y][3])

pixels = ', '.join('0x%02X' % b for b in pixels)
pixels = '\n'.join(textwrap.wrap(pixels))
pixels = textwrap.indent(pixels, '\t\t')

dump = sys.stdout

dump.write('''
struct DroidSansMonoStructure {
	int char_width;
	int char_height;
	int glyph_width;
	int glyph_height;
	int texture_width;
	int texture_height;
	unsigned char texture_pixels[%d];
};

const DroidSansMonoStructure DroidSansMono = {
	.char_width = %d,
	.char_height = %d,
	.glyph_width = %d,
	.glyph_height = %d,
	.texture_width = %d,
	.texture_height = %d,
	.texture_pixels = {
%s
	}
};
'''.strip() % (w * h, width, height, padded_width, padded_height, w, h, pixels))

dump.close()
