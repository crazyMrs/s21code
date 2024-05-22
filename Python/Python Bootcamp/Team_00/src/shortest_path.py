import os
import json
import argparse
from typing import Tuple, Dict, List, Union
from collections import deque


def get_wiki_file_path():
    user = os.environ.get("USER")
    default_path = f"/Users/{user}/Python_Bootcamp.Team_00-1/src/wiki.json"
    return os.environ.get("WIKI_FILE", default=default_path)


def read_json_from_file() -> dict:
    with open(get_wiki_file_path(), "r") as json_file:
        json_content = json.load(json_file)
    return json_content


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--from", dest="link_from", default="Python", help="Start link")
    parser.add_argument("-t", "--to", dest="link_to", default="History", help="End link")
    parser.add_argument("-v", "--verbose", dest="verbose", action="store_true", help="Enable verbose output")
    return parser.parse_args()


def get_neighbors(content: Dict, node: str) -> List[str]:
    if node in content:
        neighbors = content[node]
        if isinstance(neighbors, dict):
            return list(neighbors.keys())
        elif isinstance(neighbors, list):
            return neighbors

    for key, value in content.items():
        if isinstance(value, list) and node in value:
            return value
    return []


def process_neighbors(queue: deque, visited: set, neighbors: List[str], path: List[str], link_to: str) -> Union[Tuple[int, str], None]:
    for neighbor in neighbors:
        if neighbor not in visited:
            if neighbor == link_to:
                return len(path), "->".join(path + [neighbor])
            queue.append((neighbor, path + [neighbor]))
            visited.add(neighbor)
    return None


def process_nested_neighbors(queue: deque, visited: set, content: Dict, neighbors: List[str], path: List[str], link_to: str) -> Union[Tuple[int, str], None]:
    for neighbor in neighbors:
        sub_dict = content.get(neighbor, {})
        if sub_dict:
            if isinstance(sub_dict, dict):
                for sub_key in sub_dict.keys():
                    if sub_key not in visited:
                        if sub_key == link_to:
                            return len(path) + 1, "->".join(path + [neighbor, sub_key])
                        queue.append((sub_key, path + [neighbor, sub_key]))
                        visited.add(sub_key)
            elif isinstance(sub_dict, list):
                for sub_item in sub_dict:
                    if sub_item not in visited:
                        if sub_item == link_to:
                            return len(path) + 1, "->".join(path + [neighbor, sub_item])
                        queue.append((sub_item, path + [neighbor, sub_item]))
                        visited.add(sub_item)
    return None


def find_shortest_path(content: Dict, link_from: str, link_to: str) -> Tuple[int, str]:
    if link_from == link_to:
        return 0, link_from

    queue = deque([(link_from, [link_from])])
    visited = set()

    while queue:
        current_node, path = queue.popleft()
        visited.add(current_node)

        neighbors = get_neighbors(content, current_node)

        result = process_neighbors(queue, visited, neighbors, path, link_to)
        if result:
            return result

        result = process_nested_neighbors(queue, visited, content, neighbors, path, link_to)
        if result:
            return result

    return -1, ""


def main():
    args = parse_args()
    link_from = args.link_from
    link_to = args.link_to
    content = read_json_from_file()

    if "database not found" in content:
        print("database not found")
    else:
        shortest_path_length, shortest_path_keys = find_shortest_path(content, link_from, link_to)
        if args.verbose:
            print(shortest_path_keys)
        print(f"Shortest path length: {shortest_path_length}")


if __name__ == "__main__":
    main()
