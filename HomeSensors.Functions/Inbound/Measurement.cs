using Newtonsoft.Json;

namespace HomeSensors.Functions.Inbound;

public record Measurement
{
    [JsonProperty("t", Required = Required.Always)]
    public double Temperature { get; init; }

    [JsonProperty("h", Required = Required.Always)]
    public double Humidity { get; init; }

    [JsonProperty("U", Required = Required.Always)]
    public double Voltage { get; init; }
}
