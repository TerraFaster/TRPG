from PIL import Image, ImageDraw, ImageFont


CHARACTER_SIZE = 16 # Size of each character in pixels
ATLAS_COLUMNS = 16 # Number of columns in the font atlas
CHARACTER_ROWS = 6 # Number of rows, sufficient for 96 characters (ASCII 32 to 127)

texture_width = ATLAS_COLUMNS * CHARACTER_SIZE
texture_height = CHARACTER_ROWS * CHARACTER_SIZE

font_path = "Pixel.ttf"
output_path = "font.png"


def main():
    # Create a new image with white background
    image = Image.new("RGBA", (texture_width, texture_height), (255, 255, 255, 0))
    draw = ImageDraw.Draw(image)

    # Load the font
    try:
        font = ImageFont.truetype(font_path, CHARACTER_SIZE)
    except IOError:
        print(f"Could not load font at {font_path}")
        exit()

    # Draw each character in the ASCII range from 32 to 127
    for i in range(96):
        char = chr(32 + i)  # Start at ASCII 32
        x = (i % ATLAS_COLUMNS) * CHARACTER_SIZE
        y = (i // ATLAS_COLUMNS) * CHARACTER_SIZE
        draw.text((x, y), char, font=font, fill=(255, 255, 255, 255))  # White text

    # Save the image as a .png file
    image.save(output_path)
    print(f"Font texture saved as {output_path}")


if __name__ == "__main__":
    main()
