import pytest


def fix_wiring(cables, sockets, plugs):
    filtered_sockets = filter(lambda s: isinstance(s, str) and s.startswith("socket"), sockets)
    filtered_cables = filter(lambda s: isinstance(s, str) and s.startswith("cable"), cables)
    filtered_plugs = filter(lambda s: isinstance(s, str) and s.startswith("plug"), plugs)
    for cable, socket, plug in zip(filtered_cables, filtered_sockets, filtered_plugs):
        yield f"plug {cable} into {socket} using {plug}"

    remaining_cables = cables[len(plugs):]
    remaining_sockets = sockets[len(plugs):]
    for cable, socket in zip(remaining_cables, remaining_sockets):
        yield f"weld {cable} to {socket} without plug"


def test_fix_wiring_case1():
    plugs = ['plugZ', None, 'plugY', 'plugX']
    sockets = [1, 'socket1', 'socket2', 'socket3', 'socket4']
    cables = ['cable2', 'cable1', False]
    expected_output = [
        "plug cable2 into socket1 using plugZ",
        "plug cable1 into socket2 using plugY",
    ]
    assert list(fix_wiring(cables, sockets, plugs)) == expected_output


def test_fix_wiring_case2():
    plugs = ['plug1', 'plug2', 'plug3']
    sockets = ['socket1', 'socket2', 'socket3', 'socket4']
    cables = ['cable1', 'cable2', 'cable3', 'cable4']
    expected_output = [
        "plug cable1 into socket1 using plug1",
        "plug cable2 into socket2 using plug2",
        "plug cable3 into socket3 using plug3",
        "weld cable4 to socket4 without plug"
    ]
    assert list(fix_wiring(cables, sockets, plugs)) == expected_output


if __name__ == "__main__":
    pytest.main([__file__])

    plugs = ['plugZ', None, 'plugY', 'plugX']
    sockets = [1, 'socket1', 'socket2', 'socket3', 'socket4']
    cables = ['cable2', 'cable1', False]

    for c in fix_wiring(cables, sockets, plugs):
        print(c)
