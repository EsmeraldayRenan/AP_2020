from sanic import Sanic
from sanic.response import json


app = Sanic('Web_Api_iris')


def get_db():
    from motor.motor_asyncio import AsyncIOMotorClient
    mongo_uri = "mongodb://localhost:27017/WebApi"
    client = AsyncIOMotorClient(mongo_uri)
    return client['WebApi']


@app.route('/GetDat', methods=['GET'])
async def get(request):
    db = get_db()
    docs = await db.Interruptor.find().to_list(length=100)
    for doc in docs:
        doc['id'] = str(doc['_id'])
        del doc['_id']
    return json(docs)

@app.route('/PostDat', methods=['POST'])
async def new(request):
    doc = request.json
    print(doc)
    db = get_db()
    R = await db.Interruptor.insert_one(doc)
    return json({'object_id': str(R)})


if __name__ == "__main__":
    app.run(host='192.168.0.36', port=8080)
