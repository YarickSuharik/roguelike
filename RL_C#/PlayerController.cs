namespace RL;

public sealed class PlayerController : BaseController
{
    public PlayerController()
    {
        Console.WriteLine("[PlayerController] Constructor");
    }

    ~PlayerController()
    {
        Console.WriteLine("[PlayerController] Finalizer");
    }

    public override void MakeStep()
    {
        Character? character = PossessedCharacter;

        if (character is null) return;

        while (true)
        {
            ConsoleKeyInfo keyInfo = Console.ReadKey(intercept: true);

            int dx = 0;
            int dy = 0;
            bool wantsToMove = false;

            switch (char.ToLowerInvariant(keyInfo.KeyChar))
            {
                case 'q': dx = -1; dy = -1; wantsToMove = true; break;
                case 'w': dx = 0; dy = -1; wantsToMove = true; break;
                case 'e': dx = 1; dy = -1; wantsToMove = true; break;
                case 'a': dx = -1; dy = 0; wantsToMove = true; break;
                case 'd': dx = 1; dy = 0; wantsToMove = true; break;
                case 'z': dx = -1; dy = 1; wantsToMove = true; break;
                case 'x': dx = 0; dy = 1; wantsToMove = true; break;
                case 'c': dx = 1; dy = 1; wantsToMove = true; break;
            }

            if (wantsToMove && character.MoveRelative(dx, dy)) return;
        }
    }

    public override BaseController Clone() => new PlayerController();

    public override string Describe() => base.Describe() + " -> keyboard input";
}