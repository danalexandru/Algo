# pip install Flask
# python hello-flask.py

from flask import Flask
from flask import request

app = Flask(__name__)

@app.route("/")
def hello():
    print(request.url)
    print(request.headers["user-agent"])
    return "Hello World!"

if __name__ == "__main__":
    app.run()