import pytest

from random import randrange


def emit_gel(step):
    while True:
        yield randrange(0, 101, step)


def valve(emit_gel, step):
    gel_pressure = next(emit_gel)
    while True:
        if gel_pressure < 20 or gel_pressure > 80:
            step = -step
        gel_pressure = emit_gel.send(step)
        if gel_pressure > 90 or gel_pressure < 10:
            emit_gel.close()
            break


@pytest.mark.parametrize("step", [1, 5, 10])
def test_emit_gel(step):
    gel_generator = emit_gel(step)
    for _ in range(1000):
        pressure = next(gel_generator)
        assert 0 <= pressure <= 100


if __name__ == "__main__":
    pytest.main([__file__])
