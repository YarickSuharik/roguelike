namespace RL;

public class Actor
{
    public string Name { get; }
    public char Symbol { get; }
    public Position Location { get; private set; }
    protected World? WorldContext { get; }

    public Actor(string name, Position startPosition, World? worldContext, char symbol)
    {
        Name = name;
        Symbol = symbol;
        Location = startPosition;
        WorldContext = worldContext;
    }

    // в C# нет детерминированного деструктора: это финализатор, его вызывает сборщик мусора
    ~Actor()
    {
        Console.WriteLine($"[Actor] Finalizer: {Name} collected.");
    }

    public virtual void OnSpawned() { }

    public virtual bool OnCollisionEvent() => true;

    public bool SetActorLocation(Position newPosition)
    {
        if (WorldContext is null) return false;
        if (!WorldContext.CanMoveTo(this, newPosition)) return false;

        Location = newPosition;
        WorldContext.NotifyCameraRefresh();
        return true;
    }

    public override string ToString() => $"{Name} [{Symbol}] at {Location}";
}
