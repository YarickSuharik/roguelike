namespace RL;

public abstract class Controller
{
    public Character? PossessedCharacter { get; protected set; }

    ~Controller()
    {
        Console.WriteLine("[Controller] Finalizer: Controller collected.");
    }

    public virtual void Possess(Character character)
    {
        PossessedCharacter = character;
    }

    public abstract void Update();
}
