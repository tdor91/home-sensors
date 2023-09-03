using Newtonsoft.Json;
using System;

namespace HomeSensors.Functions.Inbound;

public record MeasurementRequest
{
    [JsonProperty("sensorId", Required = Required.Always)]
    public string SensorId { get; init; }
    
    [JsonProperty("version", Required = Required.Always)]
    public string Version { get; init; }
    
    [JsonProperty("timestamp")]
    public DateTimeOffset? Timestamp { get; init; }
    
    [JsonProperty("data", Required = Required.Always)]
    public Measurement Data { get; init; }
}
