using HomeSensors.Functions.Domain;
using System;
using System.Threading.Tasks;

namespace HomeSensors.Functions.Persistance;

public class MultiStore : IMeasurementStore
{
    public Task Persist(string sensorId, Measurement measurement)
    {
        throw new NotImplementedException();
    }
}
