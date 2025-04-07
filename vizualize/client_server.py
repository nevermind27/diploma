from http.server import HTTPServer, SimpleHTTPRequestHandler
import os
import sys

class CORSRequestHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        # Добавляем CORS заголовки
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        super().end_headers()

    def do_OPTIONS(self):
        # Обработка preflight запросов
        self.send_response(200)
        self.end_headers()

def run(port=8000):
    server_address = ('', port)
    httpd = HTTPServer(server_address, CORSRequestHandler)
    print(f"Сервер запущен на http://localhost:{port}")
    print("Нажмите Ctrl+C для остановки")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nСервер остановлен")
        httpd.server_close()

if __name__ == '__main__':
    # Проверяем, существует ли директория для тайлов
    if not os.path.exists('tiles'):
        os.makedirs('tiles')
        print("Создана директория для тайлов")
    
    # Запускаем сервер
    run() 