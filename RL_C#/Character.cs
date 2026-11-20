namespace RL;

public class Character : Actor
{
    public Character(string name, Position startPosition, World? worldContext, char symbol)
        : base(name, startPosition, worldContext, symbol)
    {
        AvailableSteps = 1;
        Console.WriteLine($"[Character] Constructor: {Name}");
    }

    public BaseController? Controller { get; private set; }

    public int AvailableSteps { get; private set; }

    public void SetController(BaseController? controller)
    {
        Controller = controller;
        controller?.Possess(this);
    }

    public void SetAvailableSteps(int steps) => AvailableSteps = steps > 0 ? steps : 0;

    public bool MoveRelative(int dx, int dy)
    {
        if (WorldContext is null) return false;

        return SetActorLocation(new Position(Location.X + dx, Location.Y + dy));
    }

    // поверхностная копия: MemberwiseClone делит с оригиналом все ссылки
    public virtual Character ShallowCopy() => (Character)MemberwiseClone();

    public virtual Character Clone()
    {
        Character copy = (Character)MemberwiseClone();
        copy.Controller = Controller?.Clone();
        return copy;
    }

    public override string ToString() =>
        $"{base.ToString()} controller={(Controller is null ? "none" : Controller.GetType().Name)}";
}