#include "Region.h"


/**
 * @brief
 * @param
 */
void Region::addNode(Region* node) {
  _nodes.push_back(node);
}


/**
 * @brief
 * @returns
 */
std::vector<Region*> Region::getNodes() {
  return _nodes;
}


/**
 * @brief
 * @returns
 */
std::map<int, Halfspace*> Region::getAllSurfaces() {
  std::map<int, Halfspace*> all_surfaces;
  std::map<int, Halfspace*> node_surfaces;
  std::vector<Region*>::iterator iter;

  for (iter = _nodes.begin(); iter != _nodes.end(); iter++) {
    node_surfaces = (*iter)->getAllSurfaces();
    all_surfaces.insert(node_surfaces.begin(), node_surfaces.end());
  }

  return all_surfaces;
}


/**
 * @brief Return the minimum reachable x-coordinate in the Region.
 * @return the minimum x-coordinate
 */
double Region::getMinX() {

  /* Set a default min-x */
  double min_x = -std::numeric_limits<double>::infinity();

  /* Loop over all nodes in the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter)
    min_x = std::max(min_x, (*iter)->getMinX());

  return min_x;
}


/**
 * @brief Return the maximum reachable x-coordinate in the Region.
 * @return the maximum x-coordinate
 */
double Region::getMaxX() {

  /* Set a default max-x */
  double max_x = std::numeric_limits<double>::infinity();

  /* Loop over all nodes in the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter)
    max_x = std::min(max_x, (*iter)->getMaxX());

  return max_x;
}


/**
 * @brief Return the minimum reachable y-coordinate in the Region.
 * @return the minimum y-coordinate
 */
double Region::getMinY() {

  /* Set a default min-y */
  double min_y = -std::numeric_limits<double>::infinity();

  /* Loop over all nodes in the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter)
    min_y = std::max(min_y, (*iter)->getMinY());

  return min_y;
}


/**
 * @brief Return the maximum reachable y-coordinate in the Region.
 * @return the maximum y-coordinate
 */
double Region::getMaxY() {

  /* Set a default max-y */
  double max_y = std::numeric_limits<double>::infinity();

  /* Loop over all nodes in the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter)
    max_y = std::min(max_y, (*iter)->getMaxY());

  return max_y;
}


/**
 * @brief Return the minimum reachable z-coordinate in the Region.
 * @return the minimum z-coordinate
 */
double Region::getMinZ() {

  /* Set a default min-z */
  double min_z = -std::numeric_limits<double>::infinity();

  /* Loop over all nodes in the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter)
    min_z = std::max(min_z, (*iter)->getMinZ());

  return min_z;
}


/**
 * @brief Return the maximum reachable z-coordinate in the Region.
 * @return the maximum z-coordinate
 */
double Region::getMaxZ() {

  /* Set a default max-z */
  double max_z = std::numeric_limits<double>::infinity();

  /* Loop over all nodes in the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter)
    max_z = std::min(max_z, (*iter)->getMaxZ());

  return max_z;
}


/**
 * @brief Return the boundary condition (REFLECTIVE, VACUUM, or INTERFACE) at
 *        the minimum reachable x-coordinate in the Region.
 * @return the boundary condition at the minimum x-coordinate
 */
boundaryType Region::getMinXBoundaryType() {

  /* Set a default min-x and boundary type*/
  double min_x = -std::numeric_limits<double>::infinity();
  boundaryType bc = BOUNDARY_NONE;

  /* Loop over all nodes inside the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter) {
    if (min_x < (*iter)->getMinX()) {
      min_x = (*iter)->getMinX();
      bc = (*iter)->getMinXBoundaryType();
    }
  }

  return bc;
}


/**
 * @brief Return the boundary condition (REFLECTIVE, VACUUM, or INTERFACE) at
 *        the maximum reachable x-coordinate in the Region.
 * @return the boundary condition at the maximum x-coordinate
 */
boundaryType Region::getMaxXBoundaryType() {

  /* Set a default max-x and boundary type*/
  double max_x = std::numeric_limits<double>::infinity();
  boundaryType bc = BOUNDARY_NONE;

  /* Loop over all nodes inside the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter) {
    if (max_x > (*iter)->getMaxX()) {
      max_x = (*iter)->getMaxX();
      bc = (*iter)->getMaxXBoundaryType();
    }
  }

  return bc;
}


/**
 * @brief Return the boundary condition (REFLECTIVE, VACUUM, or INTERFACE) at
 *        the minimum reachable y-coordinate in the Region.
 * @return the boundary condition at the minimum y-coordinate
 */
boundaryType Region::getMinYBoundaryType() {

  /* Set a default min-y and boundary type*/
  double min_y = -std::numeric_limits<double>::infinity();
  boundaryType bc = BOUNDARY_NONE;

  /* Loop over all nodes inside the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter) {
    if (min_y < (*iter)->getMinY()) {
      min_y = (*iter)->getMinY();
      bc = (*iter)->getMinYBoundaryType();
    }
  }

  return bc;
}


/**
 * @brief Return the boundary condition (REFLECTIVE, VACUUM, or INTERFACE) at
 *        the maximum reachable y-coordinate in the Region.
 * @return the boundary condition at the maximum y-coordinate
 */
boundaryType Region::getMaxYBoundaryType() {

  /* Set a default max-y and boundary type*/
  double max_y = std::numeric_limits<double>::infinity();
  boundaryType bc = BOUNDARY_NONE;

  /* Loop over all nodes inside the Region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter) {
    if (max_y > (*iter)->getMaxY()) {
      max_y = (*iter)->getMaxY();
      bc = (*iter)->getMaxYBoundaryType();
    }
  }

  return bc;
}


/**
 * @brief
 * @param
 * @returns
 */
Intersection* Region::getIntersection(Region* other) {
  // FIXME: This is memory leak hell
  Intersection* new_intersection = new Intersection();

  std::vector<Region*> other_nodes = other->getNodes();
  std::vector<Region*>::iterator iter;
  for (iter = other_nodes.begin(); iter != other_nodes.end(); iter++)
    new_intersection->addNode(*iter);

  return new_intersection;
}


/**
 * @brief
 * @param
 * @returns
 */
Union* Region::getUnion(Region* other) {
  // FIXME: This is memory leak hell
  Union* new_union = new Union();

  std::vector<Region*> other_nodes = other->getNodes();
  std::vector<Region*>::iterator iter;
  for (iter = other_nodes.begin(); iter != other_nodes.end(); iter++)
    new_union->addNode(*iter);

  return new_union;
}


/**
 * @brief
 * @returns
 */
Complement* Region::getInversion() {
  // FIXME: This is memory leak hell
  Complement* new_complement = new Complement();
  new_complement->addNode(this);
  return new_complement;
}


/**
 * @brief FIXME: Should this delete the nodes???
 */
Region* Region::clone() {

  /* Instantiate appropriate class type for the clone */
  Region* clone;
  if (dynamic_cast<Intersection*>(this))
    clone = new Intersection();
  else if (dynamic_cast<Union*>(this))
    clone = new Union();
  else if (dynamic_cast<Complement*>(this))
    clone = new Complement();

  /* Add clones of this region's nodes to the cloned region */
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); iter++)
    clone->addNode((*iter)->clone());
  return clone;
}



/**
 * @brief
 * @param
 * @returns
 */
Intersection* Intersection::getIntersection(Region* other) {

  std::vector<Region*> other_nodes = other->getNodes();
  std::vector<Region*>::iterator iter;
  Intersection* new_intersection = new Intersection();

  for (iter = _nodes.begin(); iter != _nodes.end(); iter++)
    new_intersection->addNode(*iter);

  for (iter = other_nodes.begin(); iter != other_nodes.end(); iter++)
    new_intersection->addNode(*iter);

  return new_intersection;
}


/**
 * @brief FIXME: Rename this for the ray tracing code convention
 * @param
 * @returns
 */
bool Intersection::containsPoint(Point* point) {
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); iter++) {
    if (!(*iter)->containsPoint(point))
      return false;
  }
  return true;
}


/**
 * @brief Computes the minimum distance to a Surface in the Intersection from
 *        a point with a given trajectory at a certain angle stored in a
 *        LocalCoords object.
 * @details If the trajectory will not intersect any of the Surfaces in the
 *          Intersection returns INFINITY.
 * @param coords a pointer to a localcoords
 */
double Intersection::minSurfaceDist(LocalCoords* coords) {

  double curr_dist;
  double min_dist = INFINITY;

  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter) {
    curr_dist = (*iter)->minSurfaceDist(coords);

    /* If the distance to Cell is less than current min distance, update */
    if (curr_dist < min_dist)
      min_dist = curr_dist;
  }

  return min_dist;
}



/**
 * @brief
 * @param
 * @returns
 */
Union* Union::getUnion(Region* other) {

  std::vector<Region*> other_nodes = other->getNodes();
  std::vector<Region*>::iterator iter;
  Union* new_union = new Union();  

  for (iter = _nodes.begin(); iter != _nodes.end(); iter++)
    new_union->addNode(*iter);

  for (iter = other_nodes.begin(); iter != other_nodes.end(); iter++)
    new_union->addNode(*iter);

  return new_union;
}


/**
 * @brief FIXME: Rename this for the ray tracing code convention
 * @param
 * @returns
 */
bool Union::containsPoint(Point* point) {
  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); iter++) {
    if ((*iter)->containsPoint(point))
      return true;
  }
  return false;
}


/**
 * @brief Computes the minimum distance to a Surface in the Union from
 *        a point with a given trajectory at a certain angle stored in a
 *        LocalCoords object.
 * @details If the trajectory will not intersect any of the Surfaces in the
 *          Union returns INFINITY.
 * @param coords a pointer to a localcoords
 */
double Union::minSurfaceDist(LocalCoords* coords) {

  double curr_dist;
  double min_dist = INFINITY;

  std::vector<Region*>::iterator iter;
  for (iter = _nodes.begin(); iter != _nodes.end(); ++iter) {
    curr_dist = (*iter)->minSurfaceDist(coords);

    /* If the distance to Cell is less than current min distance, update */
    if (curr_dist < min_dist)
      min_dist = curr_dist;
  }

  return min_dist;
}


/**
 * @brief FIXME: Rename this for the ray tracing code convention
 * @param @returns
 */
bool Complement::containsPoint(Point* point) {
  if (_nodes.size() > 0)
    return false;
  else
    return _nodes[0]->containsPoint(point);
}


/**
 * @brief Computes the minimum distance to a Surface in the Complement from
 *        a point with a given trajectory at a certain angle stored in a
 *        LocalCoords object.
 * @details If the trajectory will not intersect any of the Surfaces in the
 *          Complement returns INFINITY.
 * @param coords a pointer to a localcoords
 */
double Complement::minSurfaceDist(LocalCoords* coords) {
  if (_nodes.size() > 0)
    return INFINITY;
  else
    return _nodes[0]->minSurfaceDist(coords);
}


/**
 * @brief
 * @param
 * @param
 */
Halfspace::Halfspace(int halfspace, Surface* surface) {

  if (halfspace != -1 && halfspace != +1)
    log_printf(ERROR, "Unable to create halfspace from surface %d since the "
	       "halfspace %d is not -1 or 1", surface->getId(), halfspace);

  _surface = surface;
  _halfspace = halfspace;
}

/**
 * @brief FIXME: Should this delete the nodes???
 */
Halfspace::~Halfspace() { }


/**
 * @brief FIXME: Should this delete the nodes???
 */
Halfspace* Halfspace::clone() {
  Halfspace* clone = new Halfspace(_halfspace, _surface);
  return clone;
}


/**
 * @brief
 * @param
 */
Surface* Halfspace::getSurface() {
  return _surface;
}


/**
 * @brief
 * @param
 */
int Halfspace::getHalfspace() {
  return _halfspace;
}


/**
 * @brief
 * @param
 */
void Halfspace::addNode(Region* node) {
  // FIXME: WTF
  return;
  //  _nodes.push_back(node);
}


/**
 * @brief This may be bullshit
 * @returns
 */
std::vector<Region*> Halfspace::getNodes() {
  std::vector<Region*> nodes;
  nodes.push_back(this);
  return nodes;
}


/**
 * @brief
 * @returns
 */
std::map<int, Halfspace*> Halfspace::getAllSurfaces() {
  std::map<int, Halfspace*> all_surfaces;
  all_surfaces[_surface->getId()] = this;
  return all_surfaces;
}


/**
 * @brief Return the minimum reachable x-coordinate in the Halfspace.
 * @return the minimum x-coordinate
 */
double Halfspace::getMinX() {
  return _surface->getMinX(_halfspace);
}


/**
 * @brief Return the maximum reachable x-coordinate in the Halfspace.
 * @return the maximum x-coordinate
 */
double Halfspace::getMaxX() {
  return _surface->getMaxX(_halfspace);
}


/**
 * @brief Return the minimum reachable y-coordinate in the Halfspace.
 * @return the minimum y-coordinate
 */
double Halfspace::getMinY() {
  return _surface->getMinY(_halfspace);
}


/**
 * @brief Return the maximum reachable y-coordinate in the Halfspace.
 * @return the maximum y-coordinate
 */
double Halfspace::getMaxY() {
  return _surface->getMaxY(_halfspace);
}


/**
 * @brief Return the minimum reachable z-coordinate in the Halfspace.
 * @return the minimum z-coordinate
 */
double Halfspace::getMinZ() {
  return _surface->getMinZ(_halfspace);
}


/**
 * @brief Return the maximum reachable z-coordinate in the Halfspace.
 * @return the maximum z-coordinate
 */
double Halfspace::getMaxZ() {
  return _surface->getMaxZ(_halfspace);
}


/**
 * @brief Return the boundary condition (REFLECTIVE, VACUUM, or INTERFACE) of
 *        the Halfspace's Surface.
 * @return the boundary condition
 */
boundaryType Halfspace::getMinXBoundaryType() {
  return _surface->getBoundaryType();
}


/**
 * @brief Return the boundary condition (REFLECTIVE, VACUUM, or INTERFACE) of
 *        the Halfspace's Surface.
 * @return the boundary condition
 */
boundaryType Halfspace::getMaxXBoundaryType() {
  return _surface->getBoundaryType();
}


/**
 * @brief Return the boundary condition (REFLECTIVE, VACUUM, or INTERFACE) of
 *        the Halfspace's Surface.
 * @return the boundary condition
 */
boundaryType Halfspace::getMinYBoundaryType() {
  return _surface->getBoundaryType();
}


/**
 * @brief Return the boundary condition (REFLECTIVE, VACUUM, or INTERFACE) of
 *        the Halfspace's Surface.
 * @return the boundary condition
 */
boundaryType Halfspace::getMaxYBoundaryType() {
  return _surface->getBoundaryType();
}


/**
 * @brief
 * @param
 * @returns
 */
Intersection* Halfspace::getIntersection(Region* other) {
  Intersection* new_intersection = new Intersection();
  new_intersection->addNode(this);

  if (dynamic_cast<Intersection*>(other)) {
    std::vector<Region*> other_nodes = other->getNodes();
    std::vector<Region*>::iterator iter;
    for (iter = other_nodes.begin(); iter != other_nodes.end(); iter++)
      new_intersection->addNode(*iter);
  }
  else
    new_intersection->addNode(other);    

  return new_intersection;
}


/**
 * @brief
 * @param
 * @returns
 */
Union* Halfspace::getUnion(Region* other) {
  Union* new_union = new Union();
  new_union->addNode(this);

  if (dynamic_cast<Union*>(other)) {
    std::vector<Region*> other_nodes = other->getNodes();
    std::vector<Region*>::iterator iter;
    for (iter = other_nodes.begin(); iter != other_nodes.end(); iter++)
      new_union->addNode(*iter);
  }
  else
    new_union->addNode(other);

  return new_union;
}


/**
 * @brief
 * @param
 * @returns
 */
Halfspace* Halfspace::getInversion() {
  // FIXME: This is memory leak hell
  Halfspace* new_halfspace = new Halfspace(-1 * _halfspace, _surface);
  return new_halfspace;
}


/**
 * @brief FIXME: Rename this for the ray tracing code convention
 * @param
 * @returns
 */
bool Halfspace::containsPoint(Point* point) {
  // FIXME: This may be an optimization over what we have now
  if (_halfspace == 1)
    return (_surface->evaluate(point) >= 0);
  else
    return (_surface->evaluate(point) < 0);
}


/**
 * @brief Computes the minimum distance to the Surface in the Halfspace from
 *        a point with a given trajectory at a certain angle stored in a
 *        LocalCoords object.
 * @details If the trajectory will not intersect the Surface in the
 *          Halfspace returns INFINITY.
 * @param coords a pointer to a localcoords
 */
double Halfspace::minSurfaceDist(LocalCoords* coords) {
  return _surface->getMinDistance(coords);
}


/**
 * @brief FIXME: Is this necessary???
 */
RectangularPrism::RectangularPrism(double width_x, double width_y,
				   double origin_x, double origin_y) {

  XPlane* min_x = new XPlane(origin_x-width_x/2.);
  XPlane* max_x = new XPlane(origin_x+width_x/2.);
  YPlane* min_y = new YPlane(origin_y-width_y/2.);
  YPlane* max_y = new YPlane(origin_y+width_y/2.);

  min_x->setName("min-x");
  max_x->setName("max-x");
  min_y->setName("min-y");
  max_y->setName("max-y");

  Halfspace* half_min_x = new Halfspace(+1, min_x);
  Halfspace* half_max_x = new Halfspace(-1, max_x);
  Halfspace* half_min_y = new Halfspace(+1, min_y);
  Halfspace* half_max_y = new Halfspace(-1, max_y);

  addNode(half_min_x);
  addNode(half_max_x);
  addNode(half_min_y);
  addNode(half_max_y);
}


/**
 * @brief
 * @param
 */
void RectangularPrism::setBoundaryType(boundaryType boundary_type) {
  std::map<int, Halfspace*> all_surfaces = getAllSurfaces();
  std::map<int, Halfspace*>::iterator iter;
  for (iter = all_surfaces.begin(); iter != all_surfaces.end(); iter++)
    iter->second->getSurface()->setBoundaryType(boundary_type);
}