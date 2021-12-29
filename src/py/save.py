from PIL import Image


def save(path, size, data):
    image = Image.frombytes('RGB', size, bytes(data))
    image.save(path)
    