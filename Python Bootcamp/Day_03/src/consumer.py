import json
import logging
import argparse
import redis

logging.basicConfig(level=logging.INFO)


def process_message(message, evil_accounts, redis_client):
    data = json.loads(message)

    if data['metadata']['to'] in evil_accounts and data['amount'] > 0:
        from_account = data['metadata']['to']
        to_account = data['metadata']['from']
        data['metadata']['from'] = from_account
        data['metadata']['to'] = to_account
        updated_message = json.dumps(data)
        logging.info(f'Processed message: {updated_message}')
        redis_client.publish('transaction', updated_message)
    else:
        logging.info(f'Processed message: {json.dumps(data)}')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-e', type=str, required=True)
    args = parser.parse_args()

    evil_accounts = set(args.e.split(','))
    print(evil_accounts)

    redis_client = redis.Redis(host='localhost', port=6379, db=0)

    pubsub = redis_client.pubsub()
    pubsub.subscribe('transaction')

    for message in pubsub.listen():
        if message['type'] == 'message':
            process_message(message['data'], evil_accounts, redis_client)


if __name__ == "__main__":
    main()
