import argparse
import logging
import json
import requests
import networkx as nx

from bs4 import BeautifulSoup
from dotenv import set_key

logging.basicConfig(level=logging.INFO)


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--page", type=str, default="Erdős number",
                        help="Name of the Wikipedia article to start from")
    parser.add_argument("-d", "--depth", type=int, default=3, help="Depth of search")
    args = parser.parse_args()
    return args


def load_viki_page(page_name: str):
    base_url = 'https://en.wikipedia.org/wiki/'
    full_url = base_url + page_name
    response = requests.get(full_url)
    if response.status_code == 200:
        return response.text
    else:
        logging.error(f"Failed to load Wikipedia page: {response.status_code}")
        return None


def extract_links(html_content: str):
    links = set()
    soap = BeautifulSoup(html_content, 'html.parser')
    link_counter = 0

    main_content = soap.find('div', {'id': 'mw-content-text'})
    if main_content:
        for link in main_content.find_all('a', href=True):
            if link_counter >= 200:
                break
            href = link['href']
            if href.startswith('/wiki/') and (':' not in href):
                href = href.replace('/wiki/', '')
                links.add(href)
                link_counter += 1

    see_also_section = soap.find('span', {'id': 'See_also'})
    if see_also_section:
        see_also_links = see_also_section.find_next('ul').find_all('a', href=True)
        for link in see_also_links:
            if link_counter >= 200:
                break
            href = link['href']
            if href.startswith('/wiki/') and (':' not in href):
                href = href.replace('/wiki/', '')
                links.add(href)
                link_counter += 1

    return links


def find_links(page_name: str):
    html_content = load_viki_page(page_name)
    if html_content:
        return extract_links(html_content)
    return set()


def make_graph(graph: nx.DiGraph, head_link: str, depth: int, visited=None):
    if depth <= 0 or graph.number_of_nodes() >= 1000:
        return graph

    if visited is None:
        visited = set()

    if head_link not in visited:
        graph.add_node(head_link)
        visited.add(head_link)

        links = find_links(head_link)

        for link in links:
            if not graph.has_node(link):
                graph.add_node(link)
            graph.add_edge(head_link, link)

        if depth > 0 and links:
            selected_link = next(iter(links))
            make_graph(graph, selected_link, depth - 1, visited)


def main():
    args = parse_args()
    set_key(".env", "DEPTH", str(args.depth))
    graph = nx.DiGraph()

    make_graph(graph, args.page, args.depth)
    nested_dict = {}
    for node in graph.nodes():
        nested_dict[node] = list(graph.successors(node))
        if len(list(graph.successors(node))) == 0:
            nested_dict.pop(node)

    with open("wiki.json", "w") as f:
        json.dump(nested_dict, f, indent=4)


if __name__ == "__main__":
    main()
