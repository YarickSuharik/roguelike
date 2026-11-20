namespace RL;

public abstract class BaseController
{
    public Character? PossessedCharacter { get; protected set; }

    protected BaseController()
    {
        Console.WriteLine("[BaseController] Constructor");
    }

    ~BaseController()
    {
        Console.WriteLine("[BaseController] Finalizer");
    }

    public virtual void Possess(Character character)
    {
        PossessedCharacter = character;
    }

    public void Update()
    {
        Character? character = PossessedCharacter;

        if (character is null) return;

        for (int i = 0; i < character.AvailableSteps; i++)
        {
            MakeStep();
        }
    }

    public abstract void MakeStep();

    public abstract BaseController Clone();

    public virtual string Describe() =>
        PossessedCharacter is null ? "BaseController idle" : $"BaseController on {PossessedCharacter.Name}";
}