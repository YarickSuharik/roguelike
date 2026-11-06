using System.Text;

namespace RL;

public static class Program
{
    private static readonly string[] MapRelativeParts = { "RL_Data", "maps", "start_room.txt" };

    public static void Main(string[] args)
    {
        try
        {
            Console.OutputEncoding = Encoding.UTF8;
        }
        catch (IOException)
        {
            // при перенаправленном выводе кодировку консоли задать нельзя
        }

        DemoReferencesAndCopies();
        DemoDispose();
        DemoGarbageCollector();

        bool interactive = !Console.IsInputRedirected;
        bool demoOnly = args.Contains("--demo-only");

        if (interactive && !demoOnly)
        {
            Console.WriteLine("\nPress any key to start the game.");
            Console.ReadKey(intercept: true);
            RunGame();
        }

        if (interactive)
        {
            Console.WriteLine("\nPress any key to exit.");
            Console.ReadKey(intercept: true);
        }
    }

    // карта ищется рядом с текущей папкой, а затем вверх от папки exe
    private static string? ResolveMapPath()
    {
        string relative = Path.Combine(MapRelativeParts);
        if (File.Exists(relative)) return relative;

        DirectoryInfo? directory = new DirectoryInfo(AppContext.BaseDirectory);

        while (directory is not null)
        {
            string candidate = Path.Combine(directory.FullName, Path.Combine(MapRelativeParts));
            if (File.Exists(candidate)) return candidate;

            directory = directory.Parent;
        }

        return null;
    }

    private static void DemoReferencesAndCopies()
    {
        Console.WriteLine("\n=== references and copies ===");

        var heroA = new Character("HeroA", new Position(1, 1), null, 'A');
        Character heroB = heroA;
        heroB.SetController(new PlayerController());
        Console.WriteLine($"[class] HeroA.Controller is null after assigning through HeroB: {heroA.Controller is null}");

        var posA = new Position(1, 1);
        Position posB = posA;
        posB.X = 9;
        Console.WriteLine($"[struct] PosA after changing PosB: {posA}");
    }

    private static void DemoDispose()
    {
        Console.WriteLine("\n=== resource release (IDisposable) ===");

        string? mapPath = ResolveMapPath();
        if (mapPath is null)
        {
            Console.WriteLine("[dispose] map file not found");
            return;
        }

        using (var source = new MapSource(mapPath))
        {
            string[] lines = source.ReadAllLines();
            Console.WriteLine($"[dispose] map read, lines: {lines.Length}");
        }

        Console.WriteLine("[dispose] this line runs after the using block");
    }

    private static void DemoGarbageCollector()
    {
        Console.WriteLine("\n=== garbage collector ===");

        CreateTemporaryActor();
        Console.WriteLine("[gc] the block is over, the object may still be alive");
        Console.WriteLine("[gc] requesting collection");
        GC.Collect();
        GC.WaitForPendingFinalizers();
        Console.WriteLine("[gc] collection finished");
    }

    private static void CreateTemporaryActor()
    {
        var ghost = new Actor("GcGhost", new Position(0, 0), null, 'G');
        Console.WriteLine($"[gc] created {ghost}");
    }

    private static void RunGame()
    {
        Console.WriteLine("\n=== game ===");

        string? mapPath = ResolveMapPath();
        if (mapPath is null)
        {
            Console.WriteLine("Failed to load map data.");
            return;
        }

        var world = new World();

        using (var source = new MapSource(mapPath))
        {
            if (!world.InitializeMap(source.ReadAllLines()))
            {
                Console.WriteLine("Failed to load map data.");
                return;
            }
        }

        Console.WriteLine($"[world] map {world.Width}x{world.Height}");

        var camera = new Camera(new Position(0, 0), 41, 31, world);
        world.RegisterCamera(camera);

        PlayerCharacter player = world.SpawnActor(w => new PlayerCharacter("Hero", new Position(5, 4), w, '@'));
        world.SetPlayerCharacter(player);
        camera.TrackedActor = player;

        Console.WriteLine($"[composition] player owns controller: {player.Controller is not null}");
        Console.WriteLine($"[aggregation] world keeps the camera created outside: {ReferenceEquals(world.CameraContext, camera)}");
        Console.WriteLine($"[rule] move into wall at (0,0) allowed: {world.CanMoveTo(player, new Position(0, 0))}");

        Console.WriteLine("\nPress any key to render the map.");
        Console.ReadKey(intercept: true);

        camera.Refresh();

        while (true)
        {
            player.Controller?.Update();
        }
    }
}
