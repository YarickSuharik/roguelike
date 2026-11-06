namespace RL;

public sealed class PlayerCharacter : Character
{
    public PlayerCharacter(string name, Position startPosition, World? worldContext, char symbol)
        : base(name, startPosition, worldContext, symbol)
    {
    }

    public override void OnSpawned()
    {
        SetController(new PlayerController());
    }
}
