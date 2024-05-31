import json
from wsgiref.simple_server import make_server
from urllib.parse import parse_qs

species_data = {
    "Cyberman": "John Lumic",
    "Dalek": "Davros",
    "Judoon": "Shadow Proclamation Convention 15 Enforcer",
    "Human": "Leonardo da Vinci",
    "Ood": "Klineman Halpen",
    "Silence": "Tasha Lem",
    "Slitheen": "Coca-Cola salesman",
    "Sontaran": "General Staal",
    "Time Lord": "Rassilon",
    "Weeping Angel": "The Division Representative",
    "Zygon": "Broton"
}

def application(environ, start_response):
    query_params = parse_qs(environ['QUERY_STRING'])

    species = query_params.get('species', [None])[0]

    if species:
        species = species.replace('%20', ' ')
        credentials = species_data.get(species, "Unknown")
        if credentials == "Unknown":
            status = '404 Not Found'
        else:
            status = '200 OK'
    else:
        status = '404 Not Found'
        credentials = "Unknown"

    response_data = json.dumps({"credentials": credentials})
    response_headers = [
        ('Content-Type', 'application/json; charset=utf-8'),
        ('Content-Length', str(len(response_data)))
    ]
    start_response(status, response_headers)

    return [response_data.encode('utf-8')]

if __name__ == '__main__':
    httpd = make_server('localhost', 8888, application)
    print("Serving on port 8888...")
    httpd.serve_forever()
