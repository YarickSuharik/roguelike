namespace RL;

public class Character : Actor
{
    public Controller? Controller { get; private set; }

    public Character(string name, Position startPosition, World? worldContext, char symbol)
        : base(name, startPosition, worldContext, symbol)
    {
    }

    public void SetController(Controller? controller)
    {
        Controller = controller;
        controller?.Possess(this);
    }

    public bool MoveRelative(int dx, int dy)
    {
        if (WorldContext is null) return false;

        return SetActorLocation(new Position(Location.X + dx, Location.Y + dy));
    }

    public override string ToString() =>
        $"{base.ToString()} controller={(Controller is null ? "none" : Controller.GetType().Name)}";
}
