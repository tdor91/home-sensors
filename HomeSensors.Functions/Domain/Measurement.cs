using System;

namespace HomeSensors.Functions.Domain
{
    public class Measurement
    {
        public required DateTimeOffset Timestamp { get; init; } = DateTimeOffset.UtcNow;

        public required double Temperature { get; init; }

        public required double Humidity { get; init; }

        public required double Voltage { get; init; }
    }
}
