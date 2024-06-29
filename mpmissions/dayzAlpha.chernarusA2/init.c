void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

  //WEATHER SETTINGS--------------------------------------
  Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits(0.0, 1.0);
	weather.GetRain().SetLimits(0.0, 1.0);
	weather.GetFog().SetLimits(0.0, 1.0);

	weather.GetOvercast().SetForecastChangeLimits(0.0, 1.0);
	weather.GetRain().SetForecastChangeLimits(0.0, 1.0);
	weather.GetFog().SetForecastChangeLimits(0.0, 1.0);

	weather.GetOvercast().SetForecastTimeLimits(1800, 1800);
	weather.GetRain().SetForecastTimeLimits(600, 600);
	weather.GetFog().SetForecastTimeLimits(1800, 1800);

	weather.GetOvercast().Set(Math.RandomFloatInclusive(0.0, 0.1), 0, 0);
	weather.GetRain().Set(Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
	weather.GetFog().Set(Math.RandomFloatInclusive(0.0, 0.1), 0, 0);

	weather.SetWindMaximumSpeed(15);
	weather.SetWindFunctionParams(0.1, 0.3, 50);

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.8, 1.0 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "BandageDressing" );
			if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 2 );

			SetRandomHealth( itemEnt );

			rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			if ( rand < 0.35 )
      {
				itemEnt = player.GetInventory().CreateInInventory( "Morphine" );
				itemEnt = player.GetInventory().CreateInInventory( "PainkillerTablets" );
				itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Kvass" );
        itemEnt = player.GetInventory().CreateInInventory( "BakedBeansCan_Opened" );
        itemEnt = player.GetInventory().CreateInInventory( "Roadflare" );
      }
			else if ( rand > 0.65 )
      {
				itemEnt = player.GetInventory().CreateInInventory( "Morphine" );
				itemEnt = player.GetInventory().CreateInInventory( "PainkillerTablets" );
				itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Cola" );
        itemEnt = player.GetInventory().CreateInInventory( "BakedBeansCan_Opened" );
        itemEnt = player.GetInventory().CreateInInventory( "Roadflare" );
      }
			else
      {
				itemEnt = player.GetInventory().CreateInInventory( "Morphine" );
				itemEnt = player.GetInventory().CreateInInventory( "PainkillerTablets" );
				itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Pipsi" );
        itemEnt = player.GetInventory().CreateInInventory( "BakedBeansCan_Opened" );
        itemEnt = player.GetInventory().CreateInInventory( "Roadflare" );
      }

			SetRandomHealth( itemEnt );
		}
		
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
			SetRandomHealth( itemClothing );
		
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}