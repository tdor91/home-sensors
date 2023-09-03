using System;
using System.Text.Json.Serialization;

namespace HomeSensors.Functions.Inbound;

public record MeasurementRequest
{
    [JsonPropertyName("sensorId")]
    public required string SensorId { get; init; }
    
    [JsonPropertyName("version")]
    public required string Version { get; init; }
    
    [JsonPropertyName("timestamp")]
    public required DateTimeOffset Timestamp { get; init; } = DateTimeOffset.UtcNow;
    
    [JsonPropertyName("data")]
    public required Measurement Data { get; init; }
}
