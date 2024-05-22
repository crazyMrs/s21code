import os
from dotenv import load_dotenv, find_dotenv
import networkx as nx
from pyvis.network import Network

from shortest_path import read_json_from_file
from cache_wiki import make_graph


def main():
    file_name = "graph.html"
    content_dict = read_json_from_file()
    g = nx.DiGraph()

    load_dotenv(find_dotenv())
    depth_ = int(os.environ.get("DEPTH"))

    for page, links in content_dict.items():
        make_graph(g, page, depth=depth_)

    params = {
        "height": 800,
        "width": 800,
        "notebook": True
    }
    n = Network(**params)
    n.from_nx(g)
    n.show(file_name)


if __name__ == "__main__":
    main()
