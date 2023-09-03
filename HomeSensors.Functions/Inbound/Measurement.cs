using System.Text.Json.Serialization;

namespace HomeSensors.Functions.Inbound;

public record Measurement
{
    [JsonPropertyName("t")]
    public required double Temperature { get; init; }

    [JsonPropertyName("h")]
    public required double Humidity { get; init; }

    [JsonPropertyName("U")]
    public required double Voltage { get; init; }
}
