import redis

red = redis.Redis()
print(red.lrange("list",0,-1))