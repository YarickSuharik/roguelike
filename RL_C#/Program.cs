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

        DemoInheritance();
        DemoOverrides();
        DemoCopyAndClone();
        DemoStringsAndThis();
        DemoStaticAndEquals();
        DemoControllerArray();

        if (Console.IsInputRedirected || args.Contains("--demo-only")) return;

        Console.WriteLine("\nPress any key to start the game.");
        Console.ReadKey(intercept: true);
        RunGame();
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

    private static void ClearScreen()
    {
        try
        {
            Console.Clear();
        }
        catch (IOException)
        {
            Console.WriteLine();
        }
    }

    private static void PauseIfInteractive()
    {
        if (Console.IsInputRedirected) return;

        Console.WriteLine("\nPress any key to continue.");
        Console.ReadKey(intercept: true);
    }

    private static void DemoInheritance()
    {
        ClearScreen();
        Console.WriteLine("=== constructors: the base constructor runs first ===");

        var skeleton = new Skeleton("Bone", new Position(0, 0), null, 'S', new List<string> { "gold" });
        Console.WriteLine($"[demo] {skeleton.Name} got inventory number {skeleton.InventoryNumber}");

        PauseIfInteractive();
    }

    private static void DemoOverrides()
    {
        ClearScreen();
        Console.WriteLine("=== Describe() through a base reference ===");

        var hero = new PlayerCharacter("DemoHero", new Position(1, 1), null, '@');
        hero.OnSpawned();

        var skeleton = new Skeleton("DemoSkeleton", new Position(2, 2), null, 'S');
        skeleton.OnSpawned();

        BaseController playerController = hero.Controller!;
        BaseController skeletonController = skeleton.Controller!;

        Console.WriteLine($"player: {playerController.Describe()}");
        Console.WriteLine($"skeleton: {skeletonController.Describe()}");

        PauseIfInteractive();
    }

    private static void DemoCopyAndClone()
    {
        ClearScreen();
        Console.WriteLine("=== shallow copy: MemberwiseClone shares the loot list ===");

        var original = new Skeleton("Original", new Position(0, 0), null, 'S', new List<string> { "gold" });
        var shallow = (Skeleton)original.ShallowCopy();
        shallow.AddLoot("bone");

        Console.WriteLine($"original loot: {original.GetLoot()}");
        Console.WriteLine($"shallow loot: {shallow.GetLoot()}");

        Console.WriteLine("\n=== deep clone: own loot list and own controller ===");

        var source = new Skeleton("Source", new Position(0, 0), null, 'S', new List<string> { "gold" });
        var clone = (Skeleton)source.Clone();
        clone.AddLoot("bone");

        Console.WriteLine($"source loot: {source.GetLoot()}");
        Console.WriteLine($"clone loot: {clone.GetLoot()}");

        PauseIfInteractive();
    }

    private static void DemoStringsAndThis()
    {
        ClearScreen();
        Console.WriteLine("=== loot as strings ===");

        Skeleton collector = new Skeleton("Collector", new Position(0, 0), null, 'S')
            .AddLoot("gold")
            .AddLoot("bone");

        Console.WriteLine($"loot: {collector.GetLoot()}");
        Console.WriteLine($"find bon: {collector.HasLoot("bon")}");
        Console.WriteLine($"find sword: {collector.HasLoot("sword")}");
        Console.WriteLine($"first item: {collector.GetFirstLoot()}");
        Console.WriteLine($"equals \"gold bone\": {collector.LootEquals("gold bone")}");
        Console.WriteLine($"equals \"gold\": {collector.LootEquals("gold")}");

        Console.WriteLine("\n=== this ===");

        var giver = new Skeleton("Giver", new Position(0, 0), null, 'S', new List<string> { "gem" });
        var keeper = new Skeleton("Keeper", new Position(0, 0), null, 'S', new List<string> { "coin" });

        giver.ShareLootWith(keeper);
        Console.WriteLine($"keeper loot after sharing: {keeper.GetLoot()}");
        Console.WriteLine($"giver loot: {giver.GetLoot()}");

        collector.TakeLootFrom(collector);
        Console.WriteLine($"collector loot after self handover: {collector.GetLoot()}");

        PauseIfInteractive();
    }

    private static void DemoStaticAndEquals()
    {
        ClearScreen();
        Console.WriteLine("=== static members and content equality ===");
        Console.WriteLine($"created before: {Skeleton.GetCreatedCount()}");

        var first = new Skeleton("First", new Position(0, 0), null, 'S', new List<string> { "gold" });
        var second = new Skeleton("Second", new Position(0, 0), null, 'S', new List<string> { "gold" });
        var third = new Skeleton("Third", new Position(0, 0), null, 'S', new List<string> { "bone" });

        Console.WriteLine($"inventory numbers: {first.InventoryNumber}, {second.InventoryNumber}, {third.InventoryNumber}");
        Console.WriteLine($"created now: {Skeleton.GetCreatedCount()}");
        Console.WriteLine($"same loot equals: {first.Equals(second)}");
        Console.WriteLine($"same loot hashes equal: {first.GetHashCode() == second.GetHashCode()}");
        Console.WriteLine($"different loot equals: {first.Equals(third)}");

        PauseIfInteractive();
    }

    private static void DemoControllerArray()
    {
        ClearScreen();
        Console.WriteLine("=== array of base controllers ===");

        BaseController[] controllers = { new PlayerController(), new AIController() };

        foreach (BaseController controller in controllers)
        {
            Console.WriteLine(controller.Describe());
        }

        BaseController clone = controllers[1].Clone();
        Console.WriteLine($"clone: {clone.Describe()}");

        PauseIfInteractive();
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

        using var source = new MapSource(mapPath);

        if (!world.InitializeMap(source.ReadAllLines()))
        {
            Console.WriteLine("Failed to load map data.");
            return;
        }

        var camera = new Camera(new Position(0, 0), 41, 31, world);
        world.RegisterCamera(camera);

        PlayerCharacter player = world.SpawnActor(w => new PlayerCharacter("Hero", new Position(5, 4), w, '@'));
        world.SetPlayerCharacter(player);
        camera.TrackedActor = player;

        Skeleton skeleton = world.SpawnActor(w => new Skeleton("Skeleton", new Position(18, 4), w, 'S'));

        camera.Refresh();

        while (true)
        {
            player.Controller?.Update();
            skeleton.Controller?.Update();
        }
    }
}