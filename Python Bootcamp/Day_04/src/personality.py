from random import randint


def generate_personality_traits():
    traits = [randint(0, 100) for _ in range(5)]
    total_sum = sum(traits)

    normalized_traits = [trait * 100 // total_sum for trait in traits]

    remainder = 100 - sum(normalized_traits)

    index_to_increase = randint(0, 4)
    normalized_traits[index_to_increase] += remainder

    return tuple(normalized_traits)


def turrets_generator():
    neuroticism, openness, conscientiousness, extraversion, agreeableness = generate_personality_traits()

    Turret = type('Turret', (object,), {
        'neuroticism': neuroticism,
        'openness': openness,
        'conscientiousness': conscientiousness,
        'extraversion': extraversion,
        'agreeableness': agreeableness,
        'shoot': lambda self: print('Shooting'),
        'search': lambda self: print('Searching'),
        'talk': lambda self: print('Talking')
    })

    return Turret


def test_turrets_generator():
    Turret = turrets_generator()

    assert hasattr(Turret, 'neuroticism')
    assert hasattr(Turret, 'openness')
    assert hasattr(Turret, 'conscientiousness')
    assert hasattr(Turret, 'extraversion')
    assert hasattr(Turret, 'agreeableness')
    assert 0 <= Turret.neuroticism <= 100
    assert 0 <= Turret.openness <= 100
    assert 0 <= Turret.conscientiousness <= 100
    assert 0 <= Turret.extraversion <= 100
    assert 0 <= Turret.agreeableness <= 100

    assert hasattr(Turret, 'shoot')
    assert hasattr(Turret, 'search')
    assert hasattr(Turret, 'talk')

    turret = Turret()
    assert turret.neuroticism + turret.openness + turret.conscientiousness + turret.extraversion + turret.agreeableness == 100

    turret.shoot()
    turret.search()
    turret.talk()


if __name__ == "__main__":
    test_turrets_generator()
