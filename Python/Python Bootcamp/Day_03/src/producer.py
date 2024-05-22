import json
import logging
import random
import redis

logging.basicConfig(level=logging.INFO)

redis_client = redis.Redis(host='localhost', port=6379, db=0)


def generate_message():
    from_account = str(random.randint(1000000000, 9999999999))
    to_account = str(random.randint(1000000000, 9999999999))

    random_amount = random.randrange(-100000, 100000, 1000)

    message = {
        "metadata": {
            "from": from_account,
            "to": to_account
        },
        "amount": random_amount
    }

    return json.dumps(message)


def main():
    message1 = {
        "metadata": {
            "from": "3333333333",
            "to": "2222222222"
        },
        "amount": random.randrange(1000, 100000, 1000)
    }

    for _ in range(1):
        redis_client.publish('transaction', json.dumps(message1))
        logging.info(f'Message: {message1}')

    message2 = {
        "metadata": {
            "from": "5555555555",
            "to": "4444444444"
        },
        "amount": random.randrange(1000, 100000, 1000)
    }

    for _ in range(1):
        redis_client.publish('transaction', json.dumps(message2))
        logging.info(f'Message: {message2}')

    for _ in range(8):
        message = generate_message()
        redis_client.publish('transaction', message)
        logging.info(f'Message: {message}')


if __name__ == "__main__":
    main()