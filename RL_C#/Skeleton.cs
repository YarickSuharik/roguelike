using LootList = System.Collections.Generic.List<string>;

namespace RL;

public class Skeleton : Character
{
    private static int createdCount;

    private LootList loot;

    public Skeleton(string name, Position startPosition, World? worldContext, char symbol, LootList? loot = null)
        : base(name, startPosition, worldContext, symbol)
    {
        this.loot = loot ?? new LootList();
        InventoryNumber = ++createdCount;
        Console.WriteLine($"[Skeleton] Constructor: {Name}");
    }

    public static int GetCreatedCount() => createdCount;

    public int InventoryNumber { get; }

    public string GetLoot() => string.Join(' ', loot);

    public string GetFirstLoot() => loot.Count > 0 ? loot[0] : string.Empty;

    public bool HasLoot(string item) => loot.Any(entry => entry.Contains(item, StringComparison.Ordinal));

    public bool LootEquals(string expected) => GetLoot() == expected;

    public Skeleton AddLoot(string item)
    {
        loot.Add(item);
        return this;
    }

    public void TakeLootFrom(Skeleton source)
    {
        if (ReferenceEquals(this, source)) return;

        AddLoot(source.GetLoot());
    }

    public void ShareLootWith(Skeleton other) => other.TakeLootFrom(this);

    public override Character ShallowCopy() => (Skeleton)MemberwiseClone();

    // глубокий клон: свой список лута и свой контроллер
    public override Character Clone()
    {
        var copy = (Skeleton)MemberwiseClone();
        copy.loot = new LootList(loot);
        copy.SetController(Controller?.Clone());
        return copy;
    }

    public override bool Equals(object? obj) => obj is Skeleton other && GetLoot() == other.GetLoot();

    public override int GetHashCode() => StringComparer.Ordinal.GetHashCode(GetLoot());

    public override void OnSpawned()
    {
        SetController(new AIController());
    }
}