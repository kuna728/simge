from PIL import Image


def load(path):
    with Image.open(path) as im:
        width, height = im.size
        imgData = list(im.getdata())
        imgData = bytes([x[i] for x in imgData for i in range(3)])
        ret = *im.size, imgData
    return ret

