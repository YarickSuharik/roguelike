namespace RL;

public class AIController : BaseController
{
    private static readonly (int Dx, int Dy)[] Directions =
    {
        (-1, -1), (0, -1), (1, -1),
        (-1, 0), (1, 0),
        (-1, 1), (0, 1), (1, 1)
    };

    public AIController()
    {
        Console.WriteLine("[AIController] Constructor");
    }

    ~AIController()
    {
        Console.WriteLine("[AIController] Finalizer");
    }

    public override void MakeStep()
    {
        Character? character = PossessedCharacter;

        if (character is null) return;

        int[] order = Enumerable.Range(0, Directions.Length).OrderBy(_ => Random.Shared.Next()).ToArray();

        foreach (int index in order)
        {
            (int dx, int dy) = Directions[index];

            if (character.MoveRelative(dx, dy)) return;
        }
    }

    public override BaseController Clone() => new AIController();

    public override string Describe() => "AIController -> random adjacent step";
}