﻿using Newtonsoft.Json;
using System;

namespace HomeSensors.Functions.Inbound;

public static class InboundMappingExtensions
{
    public static Domain.Measurement ToDomain(this MeasurementRequest measurement)
    {
        return new Domain.Measurement
        {
            Timestamp = measurement.Timestamp ?? DateTimeOffset.UtcNow,
            Temperature = measurement.Data.Temperature,
            Humidity = measurement.Data.Humidity,
            Voltage = measurement.Data.Voltage,
        };
    }

    public static string ToJson(this MeasurementRequest measurement)
    {
        return JsonConvert.SerializeObject(measurement, Formatting.Indented);
    }
}
