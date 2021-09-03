#include "flight.h"

QDate Flight::getDepartureDate() const
{
    return m_departureDate;
}
void Flight::setDepartureDate(const QDate& dd)
{
    m_departureDate = dd;
}

QTime Flight::getDepartureTime() const
{
    return m_departureTime;
}
void Flight::setDepartureTime(const QTime& dt)
{
    m_departureTime = dt;
}

QTime Flight::getFlightTime() const
{
    return m_flightTime;
}
void Flight::setFlightTime(const QTime& ft)
{
    m_flightTime = ft;
}

bool Flight::getBreakfast() const
{
    return m_breakfast;
}
void Flight::setBreakfast(const bool br)
{
    m_breakfast = br;
}

QString Flight::getAirport() const
{
    return m_airport;
}
void Flight::setAirport(const QString ap)
{
    m_airport = ap;
}
void Flight::breakfast_check()
{
    m_breakfast = ((m_flightTime.hour() > 4 || (m_flightTime.hour() == 4 && m_flightTime.minute() >= 1)));
}

Flight::Flight(const QDate& dd, const QTime& dt, const QTime& ft, const QString at)
{
    setDepartureDate(dd);
    setDepartureTime(dt);
    setFlightTime(ft);
    setAirport(at);
    breakfast_check();
}
