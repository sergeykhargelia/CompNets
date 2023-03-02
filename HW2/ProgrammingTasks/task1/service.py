from flask import Flask
from flask_restful import Api, Resource, reqparse
import random

items = {}

class OnlineStore(Resource):
    def get(self, id=None):
        if id == None:
            return items, 200

        if id in items:
            return items[id], 200
        
        return "Item not found", 404


    def delete(self, id):
        items.pop(id)
        return f"Item with id {id} is deleted.", 200

    def post(self):
        parser = reqparse.RequestParser()
        parser.add_argument("name")
        parser.add_argument("description")
        params = parser.parse_args()
        
        id = random.randint(10**9, 10**10)

        item = {
            "id" : id,
            "name" : params["name"],
            "description" : params["description"]
        }

        items[id] = item
        return item, 201

    def put(self, id):
        parser = reqparse.RequestParser()
        parser.add_argument("name")
        parser.add_argument("description")
        params = parser.parse_args()

        if id in items:
            items[id]["name"] = params["name"]
            items[id]["description"] = params["description"]
            return items[id], 200
      
        item = {
            "id": id,
            "name": params["name"],
            "description": params["description"]
        }
      
        items[id] = item
        return item, 201

    
app = Flask(__name__)
api = Api(app)

api.add_resource(OnlineStore, "/online-store", "/online-store/", "/online-store/<int:id>")
if __name__ == '__main__':
    app.run()