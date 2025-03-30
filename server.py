from fastapi import FastAPI
from fastapi.responses import FileResponse
import os

app = FastAPI()

# Директория, куда C++ код сохраняет тайлы
TILES_FOLDER = "tiles"

@app.get("/")
def get_index():
    """Отдаёт HTML страницу"""
    return FileResponse("index.html")


@app.get("/tiles")
def list_tiles():
    """Возвращает список доступных тайлов"""
    if not os.path.exists(TILES_FOLDER):
        return {"tiles": []}
    return {"tiles": sorted(os.listdir(TILES_FOLDER))}

@app.get("/tiles/{tile_name}")
def get_tile(tile_name: str):
    """Отдаёт изображение тайла по его имени"""
    tile_path = os.path.join(TILES_FOLDER, tile_name)
    if os.path.exists(tile_path):
        return FileResponse(tile_path)
    return {"error": "Tile not found"}

#uvicorn server:app --reload
