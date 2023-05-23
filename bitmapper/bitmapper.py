
import numpy as np 
import cv2 
import os
import argparse

BLUR_SIZE = 3
CANNY_THRESH1 = 100
CANNY_THRESH2 = 200
ROWS_PER_CELL = 8
COLS_PER_CELL = 5
ROW_SPACE_SIZE = 1
COL_SPACE_SIZE = 1

def calcTotalImageSize(cell_rows, cell_cols):
    """
    Given the number of cells across (cell_cols) and cells vertically (cell_rows),
    calculated the total number of pixels the image will span, including gaps between cells.
    """
    total_pixel_rows = cell_rows * ROWS_PER_CELL + (cell_rows-1) * ROW_SPACE_SIZE
    total_pixel_cols = cell_cols * COLS_PER_CELL + (cell_cols-1) * COL_SPACE_SIZE

    return (total_pixel_rows, total_pixel_cols)


def calcNumberOfCellsNeeded(image_rows, image_cols):
    """
    Given an image size, calculate the number of 
    """


def read_image_as_grayscale(file_name):
    file = os.path.join(".", file_name)

    img = cv2.imread(file)
    print("img shape {}".format(img.shape))

    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    return img_gray


def get_edge_image(img_gray):
    img_blur = cv2.GaussianBlur(img_gray, (BLUR_SIZE, BLUR_SIZE), 0)
    edges = cv2.Canny(image=img_blur, threshold1=CANNY_THRESH1, threshold2=CANNY_THRESH2)

    return edges


def get_binary_image(edges, total_rows, total_cols):
    edge_fat = cv2.dilate(edges, np.ones((21,21)), iterations=1)

    small = cv2.resize(edge_fat, (total_cols, total_rows))
    binary_image = np.where(small > 0, 1, 0).astype(np.uint8)

    return binary_image
    

def get_binary_image_code(binary_image, total_rows, total_cols):

    codeString = "uint8_t smile[{}][{}] = {{".format(total_rows, total_cols)
    for r in range(binary_image.shape[0]):
        codeString += "\n{"
        for c in range(binary_image.shape[1]):
            codeString += "{}, ".format(binary_image[r,c])
        codeString += "},"
    codeString += "\n};"

    return codeString


def split_image_into_blocks(binary_image, cell_rows, cell_cols):
    blocks = [ None for i in range(cell_rows*cell_cols)] 

    i = 0
    for r in range(cell_rows):
        for c in range(cell_cols):
            row_start = r * (ROWS_PER_CELL+ROW_SPACE_SIZE)
            col_start = c * (COLS_PER_CELL+COL_SPACE_SIZE)
            block = binary_image[row_start:row_start + ROWS_PER_CELL, col_start:col_start + COLS_PER_CELL]
            blocks[i] = block
            i = i + 1

    return blocks

def generate_code_for_binary_cell_images(binary_image, cell_rows, cell_cols):
    cell_images = split_image_into_blocks(binary_image, cell_rows, cell_cols)

    codeString = ""
    for cell_index, cell_image in enumerate(cell_images):
        codeString += f"uint8_t cell_{cell_index}[8] = {{  \n"
        for cell_row in cell_image:
            row_string = "".join([str(value) for value in cell_row])
            codeString += f"    0b000{row_string},\n"

        codeString += "    };\n"

    return codeString


def main(args):
    img_gray = read_image_as_grayscale(args.image)

    if args.debug:
        cv2.imshow("img_gray", img_gray)
        cv2.waitKey(0)

    edges = get_edge_image(img_gray)

    if args.debug:
        print("edges {}".format(edges))
        print("max edge {}".format(np.max(edges)))
        cv2.imshow("edges", edges)
        cv2.waitKey(0)

    total_rows, total_cols = calcTotalImageSize(args.rows, args.cols)
    print(f"To Size {total_rows}, {total_cols}") if args.debug else 0
    binary = get_binary_image(edges, total_rows, total_cols)

    if args.debug:
        cv2.imshow("binary", binary*255)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    
    code_string = generate_code_for_binary_cell_images(binary, args.rows, args.cols)

    print(code_string)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert an image to bitmap for one or multiple 5x8 LCD characters")
    parser.add_argument("-i", "--image", default="smile.jpg")
    parser.add_argument("-r", "--rows", help="Number of cell rows to use in the output image.", type=int, default=2, required=False)
    parser.add_argument("-c", "--cols", help="Number of cell columns to use in the output image.", type=int, default=4, required=False)
    parser.add_argument("-d", "--debug", help="Show intermediate images and more logging.", action='store_true')
    args = parser.parse_args()
    print(args)

    main(args)
